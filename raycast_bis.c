/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_bis.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acasanov <acasanov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 19:23:45 by acasanov          #+#    #+#             */
/*   Updated: 2024/07/25 17:47:41 by acasanov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/* Setup values and begin ray calculation  */
void	raycast_part_one(t_game *game, t_raycast *raycast)
{
	raycast->hit = 0;
	raycast->map_x = (int)game->player->pos_x;
	raycast->map_y = (int)game->player->pos_y;
	raycast->camera_x = 2 * raycast->x
		/ (double)game->graphics->screen_lenght - 1;
	raycast->ray_dir_x = game->player->dir_x + game->player->plane_x
		* raycast->camera_x;
	raycast->ray_dir_y = game->player->dir_y + game->player->plane_y
		* raycast->camera_x;
	raycast->delta_dist_x = fabs(1 / raycast->ray_dir_x);
	raycast->delta_dist_y = fabs(1 / raycast->ray_dir_y);
}

/* Calculate the initial distance to the sides */
void	raycast_part_two(t_game *game, t_raycast *raycast)
{
	if (raycast->ray_dir_x < 0)
	{
		raycast->step_x = -1;
		raycast->side_dist_x = (game->player->pos_x - raycast->map_x)
			* raycast->delta_dist_x;
	}
	else
	{
		raycast->step_x = 1;
		raycast->side_dist_x = (raycast->map_x + 1.0 - game->player->pos_x)
			* raycast->delta_dist_x;
	}
	if (raycast->ray_dir_y < 0)
	{
		raycast->step_y = -1;
		raycast->side_dist_y = (game->player->pos_y - raycast->map_y)
			* raycast->delta_dist_y;
	}
	else
	{
		raycast->step_y = 1;
		raycast->side_dist_y = (raycast->map_y + 1.0 - game->player->pos_y)
			* raycast->delta_dist_y;
	}
}

/* Impact test of the ray on a wall and its size */
void	raycast_part_three(t_game *game, t_raycast *raycast)
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
	}
	if (raycast->side == 0)
		raycast->perp_wall_dist = (raycast->map_x - game->player->pos_x
				+ (1 - raycast->step_x) / 2) / raycast->ray_dir_x;
	else
		raycast->perp_wall_dist = (raycast->map_y - game->player->pos_y
				+ (1 - raycast->step_y) / 2) / raycast->ray_dir_y;
}

/* Preparation of information for drawing */
void	raycast_part_four(t_game *game, t_raycast *raycast)
{
	raycast->line_height = (int)(game->graphics->screen_height
			/ raycast->perp_wall_dist);
	raycast->draw_start = -raycast->line_height / 2
		+ game->graphics->screen_height / 2;
	if (raycast->draw_start < 0)
		raycast->draw_start = 0;
	raycast->draw_end = raycast->line_height / 2
		+ game->graphics->screen_height / 2;
	if (raycast->draw_end >= game->graphics->screen_height)
		raycast->draw_end = game->graphics->screen_height - 1;
	raycast->tex_num = game->map[raycast->map_x][raycast->map_y] - 49;
	if (raycast->side == 0)
		raycast->wall_x = game->player->pos_y + raycast->perp_wall_dist
			* raycast->ray_dir_y;
	else
		raycast->wall_x = game->player->pos_x + raycast->perp_wall_dist
			* raycast->ray_dir_x;
	raycast->wall_x -= floor((raycast->wall_x));
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
