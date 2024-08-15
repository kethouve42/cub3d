/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shoot.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acasanov <acasanov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 17:53:09 by kethouve          #+#    #+#             */
/*   Updated: 2024/08/15 16:54:53 by acasanov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_cursor(t_game *game, int xstart)
{
	int	y;
	int	x;
	int	ystart;
	//int	xstart;

	ystart = (game->graphics->screen_height / 2);
	//xstart = (game->graphics->screen_lenght / 2);
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

void	shoot(t_game *game, t_player *player, int id_player)
{
	int	i = game->enemies_count - 1;
	
	enemies_sort(game->enemies, game, player);

	while (i >= 0)
	{
		if (check_shot(game, game->enemies[i]->sprite, player))
		{
			printf("Tir réussi!\n");
			game->enemies[i]->hp -= 1;
			if (game->enemies[i]->hp <= 0)
			{
				game->enemies[i]->chase_status = 0;
				game->enemies[i]->move_state = 0;
				game->enemies[i]->sprite->index = game->enemies[i]->sprite->nb - 1;
				printf("Kill !\n");
			}
			break;
		}
		if (game->gamemode == 2)
		{
			t_player *opponent;
			if (id_player == 1)
				opponent = game->player_two;
			else
				opponent = game->player;
			if (check_shot(game, opponent->sprite, player))
			{
				printf("Tir réussi!\n");
				opponent->hp -= 1;
				if (opponent->hp <= 0)
				{
					printf("==============\n== PLAYER %d ==\n==== WIN =====\n==============\n", id_player);
					close_game(game, NULL);
				}
			}
			break ;
		}
		i--;
	}
}

int	ray_intersects_wall(t_game *game, t_sprite *enemie, double ray_dir_x, double ray_dir_y, t_player *player)
{
	int		map_x;
	int		map_y;
	double	side_dist_x;   // faire une structure pour ces variable et une 2eme fonction
	double	side_dist_y;
	int		step_x;
	int		step_y;

	map_x = (int)player->pos_x;
	map_y = (int)player->pos_y;
	if (ray_dir_x < 0)
	{
		step_x = -1;
		side_dist_x = (player->pos_x - map_x) * fabs(1 / ray_dir_x);
	}
	else
	{
		step_x = 1;
		side_dist_x = (map_x + 1.0 - player->pos_x) * fabs(1 / ray_dir_x);
	}
	if (ray_dir_y < 0)
	{
		step_y = -1;
		side_dist_y = (player->pos_y - map_y) * fabs(1 / ray_dir_y);
	}
	else
	{
		step_y = 1;
		side_dist_y = (map_y + 1.0 - player->pos_y) * fabs(1 / ray_dir_y);
	}
	while (1)
	{
		if (map_x == (int)enemie->sprite_x && map_y == (int)enemie->sprite_y)
			return 0; // Pas d'intersection avec un mur
		if (side_dist_x < side_dist_y)
		{
			side_dist_x += fabs(1 / ray_dir_x);
			map_x += step_x;
		}
		else
		{
			side_dist_y += fabs(1 / ray_dir_y);
			map_y += step_y;
		}
		if (game->map[map_x][map_y] == '1')
			break ;
	}
	return 1; // Intersection avec un mur
}

double	calculate_distance(double x1, double y1, double x2, double y2) // creer une variable distance dans ennemi rafraichi a chaque frame pour mise au norme de draw sprite
{
	return (sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2)));
}

double	calculate_angle(double dr_x1, double dr_y1, double dr_x2, double dr_y2)
{
	double	dot;
	double	det;

	dot = dr_x1 * dr_x2 + dr_y1 * dr_y2;
	det = dr_x1 * dr_y2 - dr_y1 * dr_x2;
	return (fabs(atan2(det, dot)));
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
		if (shot_angle <= 0.1/distance_to_enemy && ray_intersects_wall(game, enemies, enemy_dir_x, enemy_dir_y, player) == 0)
			return (1);
	}
	else
		printf("trop loin\n");
	return (0);
}
