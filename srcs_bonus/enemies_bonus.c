/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enemies_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kethouve <kethouve@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 18:25:28 by acasanov          #+#    #+#             */
/*   Updated: 2024/08/23 15:28:35 by kethouve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	enemies_sort(t_enemie **enemies, t_game *game, t_player *player)
{
	double	dist1;
	double	dist2;
	int		i;
	int		j;

	i = 0;
	while (i < game->enemies_count - 1)
	{
		j = 0;
		while (j < game->enemies_count - i - 1)
		{
			dist1 = sqrt(pow(enemies[j]->sprite->sprite_x - player->pos_x, 2)
					+ pow(enemies[j]->sprite->sprite_y - player->pos_y, 2));
			dist2 = sqrt(pow(enemies[j + 1]->sprite->sprite_x
						- player->pos_x, 2) + pow(enemies[j + 1]
						->sprite->sprite_y - player->pos_y, 2));
			if (dist1 < dist2)
				swap_enemies(enemies[j], enemies[j + 1]);
			j++;
		}
		i++;
	}
}

void	draw_ennemies(t_game *game, t_sprite *enemie, t_player *player,
	int begin)
{
	t_ray_tex	ray_tex;
	t_sprite	*sprite;

	sprite = enemie;
	ray_tex.tex = &sprite->s_tex[sprite->index];
	draw_sprite_part_one(game, &ray_tex, sprite, player);
	draw_sprite_part_two(game, &ray_tex, ray_tex.tex, begin);
}

void	draw_opponent(t_game *game, t_player *opponent, t_player *player,
	int begin)
{
	t_ray_tex	ray_tex;
	t_sprite	*sprite;
	double		angle;

	angle = calculate_angle_opponent(opponent->dir_x, opponent->dir_y,
			opponent->pos_x - player->pos_x, opponent->pos_y - player->pos_y);
	if (angle > -45.0 && angle <= 45.0)
		opponent->sprite->index = 6 + opponent->sprite_buff;
	else if (angle > 45.0 && angle <= 135.0)
		opponent->sprite->index = 4 + opponent->sprite_buff;
	else if (angle > 135.0 || angle <= -135.0)
		opponent->sprite->index = 0 + opponent->sprite_buff;
	else
		opponent->sprite->index = 2 + opponent->sprite_buff;
	sprite = opponent->sprite;
	ray_tex.tex = &sprite->s_tex[sprite->index];
	draw_sprite_part_one(game, &ray_tex, sprite, player);
	draw_sprite_part_two(game, &ray_tex, ray_tex.tex, begin);
}

void	detection(t_game *game, t_enemie *enemie)
{
	if (enemie->sprite->sprite_x - game->player->pos_x <= 3
		&& enemie->sprite->sprite_x - game->player->pos_x >= -3)
	{
		if (enemie->sprite->sprite_y - game->player->pos_y <= 3
			&& enemie->sprite->sprite_y - game->player->pos_y >= -3)
			enemie->chase_status = 1;
	}
	else if (game->gamemode == 2)
	{
		if (enemie->sprite->sprite_x - game->player_two->pos_x <= 3
			&& enemie->sprite->sprite_x - game->player_two->pos_x >= -3)
		{
			if (enemie->sprite->sprite_y - game->player_two->pos_y <= 3
				&& enemie->sprite->sprite_y - game->player_two->pos_y >= -3)
				enemie->chase_status = 2;
		}
	}
}

void	move_enemies(t_game *game, t_enemie *enemie)
{
	if (enemie->chase_status == 1)
		chase(game, enemie, game->player);
	else if (enemie->chase_status == 2)
		chase(game, enemie, game->player_two);
	else
		ennemie_routine(game, enemie);
	if ((enemie->sprite->sprite_x - game->player->pos_x <= 0.1
			&& enemie->sprite->sprite_x - game->player->pos_x >= -0.1)
		&& (enemie->sprite->sprite_y - game->player->pos_y <= 0.1
			&& enemie->sprite->sprite_y - game->player->pos_y >= -0.1))
	{
		printf("game over\n");
		close_game(game, NULL);
	}
	else if (game->gamemode == 2)
	{
		if ((enemie->sprite->sprite_x - game->player_two->pos_x <= 0.1
				&& enemie->sprite->sprite_x - game->player_two->pos_x >= -0.1)
			&& (enemie->sprite->sprite_y - game->player_two->pos_y <= 0.1
				&& enemie->sprite->sprite_y - game->player_two->pos_y >= -0.1))
		{
			printf("game over\n");
			close_game(game, NULL);
		}
	}
}
