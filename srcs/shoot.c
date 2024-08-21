/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shoot.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acasanov <acasanov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 17:53:09 by kethouve          #+#    #+#             */
/*   Updated: 2024/08/21 16:06:13 by acasanov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_cursor(t_game *game, int xstart)
{
	int	y;
	int	x;
	int	ystart;

	ystart = (game->graphics->screen_height / 2);
	y = 0;
	while (y < 20)
	{
		x = -4;
		while (++x < 4)
			my_mlx_pixel_put(game->img, ystart - 10 + y, xstart + x, 0x000000);
		y++;
	}
	x = 0;
	while (x < 20)
	{
		y = -4;
		while (++y < 4)
			my_mlx_pixel_put(game->img, ystart + y, xstart - 10 + x, 0x000000);
		x++;
	}
	my_mlx_pixel_put(game->img, ystart,
		game->graphics->screen_lenght / 2, 0x555555);
}

int	shoot_bis(t_game *game, t_player *player, int id_player)
{
	t_player	*opponent;

	if (id_player == 1)
		opponent = game->player_two;
	else
		opponent = game->player;
	if (check_shot(game, opponent->sprite, player))
	{
		opponent->hp -= 1;
		if (opponent->hp <= 0)
		{
			printf("==============\n== PLAYER %d ==\n", id_player);
			printf("==== WIN =====\n==============\n");
			close_game(game, NULL);
		}
		return (1);
	}
	return (0);
}

void	shoot(t_game *game, t_player *player, int id_player)
{
	int	i;

	i = game->enemies_count - 1;
	enemies_sort(game->enemies, game, player);
	while (i >= 0)
	{
		if (check_shot(game, game->enemies[i]->sprite, player))
		{
			game->enemies[i]->hp -= 1;
			if (game->enemies[i]->hp <= 0)
			{
				game->enemies[i]->chase_status = 0;
				game->enemies[i]->move_state = 0;
				game->enemies[i]->sprite->index = game->enemies[i]
					->sprite->nb - 1;
			}
			break ;
		}
		if (game->gamemode == 2 && shoot_bis(game, player, id_player) == 1)
			break ;
		i--;
	}
}

int	check_shot(t_game *game, t_sprite *enemies, t_player *player)
{
	double	enemy_dir_x;
	double	enemy_dir_y;
	double	distance_to_enemy;
	double	shot_angle;

	enemy_dir_x = enemies->sprite_x - player->pos_x;
	enemy_dir_y = enemies->sprite_y - player->pos_y;
	distance_to_enemy = calculate_distance(player->pos_x,
			player->pos_y, enemies->sprite_x, enemies->sprite_y);
	if (distance_to_enemy <= 10.0)
	{
		shot_angle = calculate_angle(player->dir_x,
				player->dir_y, enemy_dir_x, enemy_dir_y);
		if (shot_angle <= 0.1 / distance_to_enemy
			&& ray_intersects_wall(game, enemies, player) == 0)
			return (1);
	}
	return (0);
}
