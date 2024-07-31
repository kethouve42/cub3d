/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shoot.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kethouve <kethouve@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 17:53:09 by kethouve          #+#    #+#             */
/*   Updated: 2024/07/31 14:29:26 by kethouve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_cursor(t_game *game)
{
	int	y;
	int	x;
	int	ystart;
	int	xstart;

	ystart = (game->graphics->screen_height / 2);
	xstart = (game->graphics->screen_lenght / 2);
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

void	shoot(t_game *game)
{
	if (check_shot(game, game->ennemie, 1))
		printf("Tir réussi!\n");
	else
		printf("Tir manqué!\n");
}

void	draw_ennemies(t_game *game, t_sprite ennemie)
{
	t_img		*tex;
	t_ray_tex	ray_tex;
	t_sprite	*sprite;

	sprite = &game->ennemie;
	tex = &sprite->s_tex;
	draw_sprite_part_one(game, &ray_tex, sprite);
	draw_sprite_part_two(game, &ray_tex, tex);
}

int	ray_intersects_wall(t_game *game, double ray_dir_x, double ray_dir_y)
{
	int		map_x;
	int		map_y;
	double	side_dist_x;   // faire une structure pour ces variable et une 2eme fonction
	double	side_dist_y;
	int		step_x;
	int		step_y;

	map_x = (int)game->player->pos_x;
	map_y = (int)game->player->pos_y;
	if (ray_dir_x < 0)
	{
		step_x = -1;
		side_dist_x = (game->player->pos_x - map_x) * fabs(1 / ray_dir_x);
	}
	else
	{
		step_x = 1;
		side_dist_x = (map_x + 1.0 - game->player->pos_x) * fabs(1 / ray_dir_x);
	}
	if (ray_dir_y < 0)
	{
		step_y = -1;
		side_dist_y = (game->player->pos_y - map_y) * fabs(1 / ray_dir_y);
	}
	else
	{
		step_y = 1;
		side_dist_y = (map_y + 1.0 - game->player->pos_y) * fabs(1 / ray_dir_y);
	}
	while (1)
	{
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
		if (map_x == (int)game->ennemie.x && map_y == (int)game->ennemie.y)
			return 0; // Pas d'intersection avec un mur
	}
	return 1; // Intersection avec un mur
}

double	calculate_distance(double x1, double y1, double x2, double y2)
{
	return (sqrt((x2 - x1) * (x2 - y1) + (y2 - y1) * (y2 - y1)));
}

double	calculate_angle(double dr_x1, double dr_y1, double dr_x2, double dr_y2)
{
	double	dot;
	double	det;

	dot = dr_x1 * dr_x2 + dr_y1 * dr_y2;
	det = dr_x1 * dr_y2 - dr_y1 * dr_x2;
	return (fabs(atan2(det, dot)));
}

int	check_shot(t_game *game, t_sprite enemies, int num_enemies)
{
	double	enemy_dir_x;
	double	enemy_dir_y;
	double	distance_to_enemy;
	double	shot_angle;
	int		i;

	i = 0;
	while (i < num_enemies)
	{
		enemy_dir_x = enemies.x - game->player->pos_x;
		enemy_dir_y = enemies.y - game->player->pos_y;
		distance_to_enemy = calculate_distance(game->player->pos_x,
				game->player->pos_y, enemies.x, enemies.y);
		if (distance_to_enemy <= 10.0)
		{
			shot_angle = calculate_angle(game->player->dir_x,
					game->player->dir_y, enemy_dir_x, enemy_dir_y);
			if (shot_angle <= 0.05 && ray_intersects_wall(game, enemy_dir_x,
					enemy_dir_y) == 0)
				return (1);
		}
		i++;
	}
	return (0);
}
