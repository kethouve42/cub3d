/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acasanov <acasanov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 14:34:37 by acasanov          #+#    #+#             */
/*   Updated: 2024/08/21 18:38:24 by acasanov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

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
	y = -1;
	while (++y < game->graphics->screen_height)
	{
		x = -1;
		while (++x < game->graphics->screen_lenght)
		{
			if (game->gamemode == 2
				&& x == game->graphics->screen_lenght / 2 - 5)
				x += 10;
			if (y > game->graphics->screen_height / 2)
				my_mlx_pixel_put(game->img, y, x, ground);
			else
				my_mlx_pixel_put(game->img, y, x, sky);
		}
	}
}

void	raycast_door(t_game *game, t_player *player, int begin, int end)
{
	t_raycast	ray_door;

	ray_door.x = begin;
	while (ray_door.x < end)
	{
		raycast_part_one(game, &ray_door, player, begin);
		raycast_part_two(game, &ray_door, player);
		raycast_part_three_door(game, &ray_door, player);
		if (ray_door.hit == 2)
			ray_door.tex = &game->graphics->tex_door;
		else if (ray_door.hit == 3)
			ray_door.tex = &game->graphics->tex_door2;
		if (ray_door.hit == 2 || ray_door.hit == 3)
		{
			raycast_part_four(game, &ray_door, player);
			raycast_part_five_door(game, &ray_door, player);
			raycast_part_six(game, &ray_door);
			game->z_buffer[ray_door.x] = ray_door.perp_wall_dist;
		}
		ray_door.x++;
	}
}

/* Draws a ray for each pixel column, and draws its point of impact */
void	raycast(t_game *game, t_player *player, int begin, int end)
{
	t_raycast	raycast;
	int			i;

	sprite_sort(game->graphics, game, player);
	enemies_sort(game->enemies, game, player);
	raycast.x = begin;
	while (raycast.x < end)
	{
		raycast_part_one(game, &raycast, player, begin);
		raycast_part_two(game, &raycast, player);
		raycast_part_three(game, &raycast, player);
		raycast_part_four(game, &raycast, player);
		raycast_part_five(game, &raycast, player);
		raycast_part_six(game, &raycast);
		game->z_buffer[raycast.x] = raycast.perp_wall_dist;
		raycast.x++;
	}
	draw_sprite(game, player, begin);
	raycast_door(game, player, begin, end);
	draw_sprite(game, player, begin);
	if (game->gamemode == 2)
		draw_cursor(game, begin + game->graphics->screen_lenght / 4 - 2);
	else
		draw_cursor(game, game->graphics->screen_lenght / 2);
}
