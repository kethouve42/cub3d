/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_bis.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acasanov <acasanov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 19:23:45 by acasanov          #+#    #+#             */
/*   Updated: 2024/07/24 15:45:30 by acasanov         ###   ########.fr       */
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

/* Determines which texture to use */
void	raycast_part_five(t_game *game, t_raycast *raycast)
{
	if (raycast->side == 0 && raycast->map_x < game->player->pos_x)
	{
		raycast->tex = &game->graphics->tex_n.tex[game->graphics->tex_n.index];
		raycast->map_side = 1;
	}
	else if (raycast->side == 0 && !(raycast->map_x < game->player->pos_x))
	{
		raycast->tex = &game->graphics->tex_s.tex[game->graphics->tex_s.index];
		raycast->map_side = 2;
	}
	else if (raycast->side == 1 && raycast->map_y < game->player->pos_y)
	{
		raycast->tex = &game->graphics->tex_w.tex[game->graphics->tex_w.index];
		raycast->map_side = 1;
	}
	else if (raycast->side == 1 && !(raycast->map_y < game->player->pos_y))
	{
		raycast->tex = &game->graphics->tex_e.tex[game->graphics->tex_e.index];
		raycast->map_side = 2;
	}
	else
		close_game(game, "Incorrect wall detection");
}

/* Retrieves the pixels from the texture and displays a column on the screen */
void	raycast_part_six(t_game *game, t_raycast *raycast)
{
	raycast->tex_x = (int)(raycast->wall_x * (double)(raycast->tex->width));
	if (raycast->side == 1 && raycast->map_side == 1)
		raycast->tex_x = raycast->tex->width - raycast->tex_x - 1;
	if (raycast->side == 0 && raycast->map_side == 2)
		raycast->tex_x = raycast->tex->width - raycast->tex_x - 1;
	raycast->y = raycast->draw_start;
	while (raycast->y < raycast->draw_end)
	{
		raycast->d = raycast->y * 256 - (game->graphics->screen_height / 2)
			* 256 + raycast->line_height * 128;
		raycast->tex_y = ((raycast->d * raycast->tex->height)
				/ raycast->line_height) / 256;
		if (raycast->tex_x >= 0 && raycast->tex_x < raycast->tex->width
			&& raycast->tex_y >= 0 && raycast->tex_y < raycast->tex->height)
			raycast->color = raycast->tex->data[raycast->tex_y
				* raycast->tex->width + raycast->tex_x];
		if ((raycast->color & 0x00FFFFFF) != 0)
			my_mlx_pixel_put(game->img, raycast->y, raycast->x, raycast->color);
		raycast->y++;
	}
}
