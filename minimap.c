/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acasanov <acasanov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 17:08:04 by acasanov          #+#    #+#             */
/*   Updated: 2024/07/25 17:21:30 by acasanov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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

	x = 0;
	y = 0;
	while (y < 16)
	{
		x = 0;
		while (x < 16)
		{
			my_mlx_pixel_put(img, y_start + y, x_start + x, color);
			x++;
		}
		y++;
	}
}

void	draw_player(t_img *img, t_player *player)
{
	draw_circle(img, player->pos_x * 16, player->pos_y * 16, 0x80d402);
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
			{
				draw_square(game->img, y * 16, x * 16, 0x000000);
				draw_square(game->img, y * 16, x * 16, 0x00F000);
			}
			else if (game->map[y][x] == '0')
			{
				draw_square(game->img, y * 16, x * 16, 0x000000);
				draw_square(game->img, y * 16, x * 16, 0x0209FF);
			}
			x++;
		}
		y++;
	}
	draw_player(game->img, game->player);
}
