/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acasanov <acasanov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 17:08:04 by acasanov          #+#    #+#             */
/*   Updated: 2024/08/14 19:11:07 by acasanov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_line(t_img *img, t_player *player, int x1, int y1)
{
	t_map	map;

	init_map_line(&map, player, x1, y1);
	while (1)
	{
		my_mlx_pixel_put(img, map.x0, map.y0, map.color);
		if (map.x0 == x1 && map.y0 == y1)
			break ;
		map.e2 = map.err;
		if (map.e2 > -(map.dx))
		{
			map.err -= map.dy;
			map.x0 += map.sx;
		}
		if (map.e2 < map.dy)
		{
			map.err += map.dx;
			map.y0 += map.sy;
		}
	}
}

void	draw_circle(t_img *img, int y_center, int x_center, int color)
{
	int	x;
	int	y;
	int	radius_squared;
	int	radius;

	radius = 5;
	radius_squared = radius * radius;
	y = -radius;
	while (y <= radius)
	{
		x = -radius;
		while (x <= radius)
		{
			if (x * x + y * y <= radius_squared)
				my_mlx_pixel_put(img, y_center + y, x_center + x, color);
			x++;
		}
		y++;
	}
}

void	draw_square(t_img *img, int y_start, int x_start, int color)
{
	int	x;
	int	y;

	y = 0;
	while (y < 16)
	{
		x = 0;
		while (x < 16)
		{
			my_mlx_pixel_put(img, y_start + y, x_start + x, 0x000000);
			x++;
		}
		y++;
	}
	y = 0;
	while (y < 15)
	{
		x = 0;
		while (x < 15)
		{
			my_mlx_pixel_put(img, y_start + y, x_start + x, color);
			x++;
		}
		y++;
	}
}

void	draw_player(t_img *img, t_player *player)
{
	int	dir_x_end;
	int	dir_y_end;

	dir_x_end = (int)(player->pos_x * 16 + player->dir_x * 15);
	dir_y_end = (int)(player->pos_y * 16 + player->dir_y * 15);
	draw_circle(img, player->pos_x * 16, player->pos_y * 16, 0x80d402);
	draw_line(img, player, dir_x_end, dir_y_end);
}

int	minimap(t_game *game)
{
	int	x;
	int	y;

	x = 0;
	y = 0;
	while (y < game->map_height)
	{
		x = 0;
		while (game->map[y][x])
		{
			if (game->map[y][x] == '1')
				draw_square(game->img, y * 16, x * 16, 0x00F000);
			else if (is_into_str(game->map[y][x], "0PB"))
				draw_square(game->img, y * 16, x * 16, 0x0B04A4);
			else if (game->map[y][x] == 'D')
				draw_square(game->img, y * 16, x * 16, 0xFF0202);
			else if (game->map[y][x] == 'd')
				draw_square(game->img, y * 16, x * 16, 0xE2F900);
			x++;
		}
		y++;
	}
	draw_player(game->img, game->player);
	draw_player(game->img, game->player_two);
}
