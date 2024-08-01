/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kethouve <kethouve@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 14:34:37 by acasanov          #+#    #+#             */
/*   Updated: 2024/08/01 18:51:28 by kethouve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/* Change the image displayed on the screen */
void	my_mlx_pixel_put(t_img *img, int y, int x, int color)
{
	char	*dst;

	dst = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

/* Change the three RGB values ​​to a single int */
int	convert_rgb_to_int(int r, int g, int b)
{
	return ((r << 16) | (g << 8) | b);
}

/* Displays the background of the screen, according to the colors of the .cub */
void	draw_skyground(t_game *game)
{
	int	ground;
	int	sky;
	int	x;
	int	y;

	ground = convert_rgb_to_int(game->graphics->color_ground[0],
			game->graphics->color_ground[1], game->graphics->color_ground[2]);
	sky = convert_rgb_to_int(game->graphics->color_sky[0],
			game->graphics->color_sky[1], game->graphics->color_sky[2]);
	y = 0;
	while (y < game->graphics->screen_height)
	{
		x = 0;
		while (x < game->graphics->screen_lenght)
		{
			if (y > game->graphics->screen_height / 2)
				my_mlx_pixel_put(game->img, y, x, ground);
			else
				my_mlx_pixel_put(game->img, y, x, sky);
			x++;
		}
		y++;
	}
}

void	raycast_door(t_game *game)
{
	t_raycast	ray_door;

	ray_door.x = 0;
	ray_door.tex = &game->graphics->tex_door;
	while (ray_door.x < (game->graphics->screen_lenght))
	{
		raycast_part_one(game, &ray_door);
		raycast_part_two(game, &ray_door);
		raycast_part_three_door(game, &ray_door);
		if (ray_door.hit == 2)
		{
			raycast_part_four(game, &ray_door);
			raycast_part_five_door(game, &ray_door);
			raycast_part_six(game, &ray_door);
			game->z_buffer[ray_door.x] = ray_door.perp_wall_dist;
		}
		ray_door.x++;
	}
}

/* Draws a ray for each pixel column, and draws its point of impact */
void	raycast(t_game *game)
{
	t_raycast	raycast;
	int			i;

	sprite_sort(game->graphics, game);
	raycast.x = 0;
	while (raycast.x < (game->graphics->screen_lenght))
	{
		raycast_part_one(game, &raycast);
		raycast_part_two(game, &raycast);
		raycast_part_three(game, &raycast);
		raycast_part_four(game, &raycast);
		raycast_part_five(game, &raycast);
		raycast_part_six(game, &raycast);
		game->z_buffer[raycast.x] = raycast.perp_wall_dist;
		raycast.x++;
	}
	draw_sprite(game);
	//draw_ennemies(game, game->enemies.sprite);
	raycast_door(game);
	draw_sprite(game);
	//draw_ennemies(game, game->enemies.sprite);
	draw_cursor(game);
}
