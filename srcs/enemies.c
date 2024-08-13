/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enemies->c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acasanov <acasanov@student->42->fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 15:26:08 by kethouve          #+#    #+#             */
/*   Updated: 2024/08/12 17:46:23 by acasanov         ###   ########->fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	get_enemie(t_game *game, char **map, int x, int y)
{
	t_enemie	*enemie;

	enemie = malloc(sizeof(t_enemie));
	enemie->hp = 3;
	enemie->n_move = 3000;
	enemie->move = enemie->n_move;
	enemie->move_state = 1;
	enemie->chase_status = 0;
	enemie->sprite = malloc(sizeof(t_sprite));
	enemie->sprite->sprite_x = y + 0.5;
	enemie->sprite->sprite_y = x + 0.5;
	enemie->sprite->s_tex = malloc(sizeof(t_img) * 3);
	enemie->sprite->s_tex[0].img = NULL;
	enemie->sprite->s_tex[1].img = NULL;
	enemie->sprite->s_tex[2].img = NULL;
	enemie->sprite->index = 0;
	enemie->sprite->nb = 3;
	enemie->sprite->s_tex[0] = game->graphics->s_enemi_one;
	enemie->sprite->s_tex[1] = game->graphics->s_enemi_two;
	enemie->sprite->s_tex[2] = game->graphics->s_enemi_dead;
	map[y][x] = '0';
	game->enemies[game->enemies_count] = enemie;
	game->enemies_count++;
}

void	swap_enemies(t_enemie *a, t_enemie *b)
{
	t_enemie	temp;

	temp = *a;
	*a = *b;
	*b = temp;
}

void	enemies_sort(t_enemie **enemies, t_game *game)
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
			dist1 = sqrt(pow(enemies[j]->sprite->sprite_x - game->player->pos_x, 2)
					+ pow(enemies[j]->sprite->sprite_y - game->player->pos_y, 2));
			dist2 = sqrt(pow(enemies[j + 1]->sprite->sprite_x - game->player->pos_x, 2)
					+ pow(enemies[j + 1]->sprite->sprite_y - game->player->pos_y, 2));
			if (dist1 < dist2)
				swap_enemies(enemies[j], enemies[j + 1]);
			j++;
		}
		i++;
	}
}

void	draw_ennemies(t_game *game, t_sprite *enemie)
{
	t_img		*tex;
	t_ray_tex	ray_tex;
	t_sprite	*sprite;

	sprite = enemie;
	tex = &sprite->s_tex[sprite->index];
	draw_sprite_part_one(game, &ray_tex, sprite);
	draw_sprite_part_two(game, &ray_tex, tex);
}

void	chase(t_game *game, t_enemie *enemie)
{
	int	temp_x;
	int	temp_y;
	
	temp_x = enemie->sprite->sprite_x;
	temp_y = enemie->sprite->sprite_y;
	if (enemie->sprite->sprite_x > game->player->pos_x)
	{
		temp_x = (int)enemie->sprite->sprite_x - 0.02 * HITBOX_SIZE;
		if (is_into_str(game->map[temp_x][temp_y], "1PDB") == 0)
			enemie->sprite->sprite_x -= 0.02;
	}
	if (enemie->sprite->sprite_x < game->player->pos_x)
	{
		temp_x = (int)enemie->sprite->sprite_x + 0.02 * HITBOX_SIZE;
		if (is_into_str(game->map[temp_x][temp_y], "1PDB") == 0)
			enemie->sprite->sprite_x += 0.02;
	}
	if (enemie->sprite->sprite_y < game->player->pos_y)
	{
		temp_y = (int)enemie->sprite->sprite_y + 0.02 * HITBOX_SIZE;
		if (is_into_str(game->map[temp_x][temp_y], "1PDB") == 0)
			enemie->sprite->sprite_y += 0.02;
	}
	if (enemie->sprite->sprite_y > game->player->pos_y)
	{
		temp_y = (int)enemie->sprite->sprite_y - 0.02 * HITBOX_SIZE;
		if (is_into_str(game->map[temp_x][temp_y], "1PDB") == 0)
			enemie->sprite->sprite_y -= 0.02;
	}
}

void	detection(t_game *game, t_enemie *enemie)
{
	if (enemie->sprite->sprite_x - game->player->pos_x <= 1
		&& enemie->sprite->sprite_x - game->player->pos_x >= -1)
	{
		if (enemie->sprite->sprite_y - game->player->pos_y <= 1
			&& enemie->sprite->sprite_y - game->player->pos_y >= -1)
		{
			printf("CHASE_ON\n");
			enemie->chase_status = 1;
		}
	}
}

void	move_enemies(t_game *game, t_enemie *enemie)
{
	int	temp_y;
	int	temp_x;

	temp_x = (int)enemie->sprite->sprite_x;
	temp_y = (int)enemie->sprite->sprite_y;
	if (enemie->chase_status == 1)
		chase(game, enemie);
	else
	{
		if (enemie->move_state == 1)
		{
			temp_x = (int)(enemie->sprite->sprite_x - 0.01 - 0.15);
			if (is_into_str(game->map[temp_x][temp_y], "1PDB") == 0)
				enemie->sprite->sprite_x -= 0.01;
			else
			{
				enemie->move = enemie->n_move + 1;
				enemie->move_state = 2;
			}
		}
		else if (enemie->move_state == 2)
		{
			temp_y = (int)(enemie->sprite->sprite_y - 0.01 - 0.15);
			if (is_into_str(game->map[temp_x][temp_y], "1PDB") == 0)
				enemie->sprite->sprite_y -= 0.01;
			else
			{
				enemie->move = enemie->n_move + 1;
				enemie->move_state = 3;
			}
		}
		else if (enemie->move_state == 3)
		{
			temp_x = (int)(enemie->sprite->sprite_x + 0.01 + 0.15);
			if (is_into_str(game->map[temp_x][temp_y], "1PDB") == 0)
				enemie->sprite->sprite_x += 0.01;
			else
			{
				enemie->move = enemie->n_move + 1;
				enemie->move_state = 4;
			}
		}
		else if (enemie->move_state == 4)
		{
			temp_y = (int)(enemie->sprite->sprite_y + 0.01 + 0.15);
			if (is_into_str(game->map[temp_x][temp_y], "1PDB") == 0)
				enemie->sprite->sprite_y += 0.01;
			else
			{
				enemie->move = enemie->n_move + 1;
				enemie->move_state = 1;
			}
		}
		enemie->move--;
		if (enemie->move == 0)
		{
			enemie->move = enemie->n_move;
			if (enemie->move_state == 1)
				enemie->move_state = 2;
			else if (enemie->move_state == 2)
				enemie->move_state = 3;
			else if (enemie->move_state == 3)
				enemie->move_state = 4;
			else
				enemie->move_state = 1;
		}
		detection(game, enemie);
	}
	if ((enemie->sprite->sprite_x - game->player->pos_x <= 0.1
		&& enemie->sprite->sprite_x - game->player->pos_x >= -0.1)
		&& (enemie->sprite->sprite_y - game->player->pos_y <= 0.1
		&& enemie->sprite->sprite_y - game->player->pos_y >= -0.1)) // a ameliorer
	{
		printf("game over\n");
		close_game(game, NULL);
	}
}
