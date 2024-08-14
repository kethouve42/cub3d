/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_ter.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acasanov <acasanov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 17:45:19 by acasanov          #+#    #+#             */
/*   Updated: 2024/08/14 18:04:25 by acasanov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/* Impact test of the ray on a wall and its size */
void	raycast_part_three_door(t_game *game, t_raycast *raycast)
{
	while (raycast->hit == 0)
	{
		if (raycast->side_dist_x < raycast->side_dist_y)
		{
			raycast->side_dist_x += raycast->delta_dist_x;
			raycast->map_x += raycast->step_x;
			raycast->side = 0;
		}
		else
		{
			raycast->side_dist_y += raycast->delta_dist_y;
			raycast->map_y += raycast->step_y;
			raycast->side = 1;
		}
		if (game->map[raycast->map_x][raycast->map_y] == '1')
			raycast->hit = 1;
		if (game->map[raycast->map_x][raycast->map_y] == 'D')
			raycast->hit = 2;
		if (game->map[raycast->map_x][raycast->map_y] == 'd')
			raycast->hit = 3;
	}
	if (raycast->side == 0)
		raycast->perp_wall_dist = (raycast->map_x - game->player->pos_x
				+ (1 - raycast->step_x) / 2) / raycast->ray_dir_x;
	else
		raycast->perp_wall_dist = (raycast->map_y - game->player->pos_y
				+ (1 - raycast->step_y) / 2) / raycast->ray_dir_y;
}

/* Determines which texture to use */
void	raycast_part_five_door(t_game *game, t_raycast *raycast)
{
	if (raycast->side == 0 && raycast->map_x < game->player->pos_x)
		raycast->map_side = 1;
	else if (raycast->side == 0 && !(raycast->map_x < game->player->pos_x))
		raycast->map_side = 2;
	else if (raycast->side == 1 && raycast->map_y < game->player->pos_y)
		raycast->map_side = 1;
	else if (raycast->side == 1 && !(raycast->map_y < game->player->pos_y))
		raycast->map_side = 2;
	else
		close_game(game, "Incorrect door detection");
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
