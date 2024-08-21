/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shoot_bis.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acasanov <acasanov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 16:05:26 by acasanov          #+#    #+#             */
/*   Updated: 2024/08/21 16:13:31 by acasanov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ray_inter_wall_bis(t_ray_wall *ray_wall, t_player *player)
{
	if (ray_wall->ray_dir_x < 0)
	{
		ray_wall->step_x = -1;
		ray_wall->side_dist_x = (player->pos_x - ray_wall->map_x)
			* fabs(1 / ray_wall->ray_dir_x);
	}
	else
	{
		ray_wall->step_x = 1;
		ray_wall->side_dist_x = (ray_wall->map_x + 1.0 - player->pos_x)
			* fabs(1 / ray_wall->ray_dir_x);
	}
	if (ray_wall->ray_dir_y < 0)
	{
		ray_wall->step_y = -1;
		ray_wall->side_dist_y = (player->pos_y - ray_wall->map_y)
			* fabs(1 / ray_wall->ray_dir_y);
	}
	else
	{
		ray_wall->step_y = 1;
		ray_wall->side_dist_y = (ray_wall->map_y + 1.0 - player->pos_y)
			* fabs(1 / ray_wall->ray_dir_y);
	}
}

int	ray_intersects_wall(t_game *game, t_sprite *enemie, t_player *player)
{
	t_ray_wall	ray_wall;

	ray_wall.ray_dir_x = enemie->sprite_x - player->pos_x;
	ray_wall.ray_dir_y = enemie->sprite_y - player->pos_y;
	ray_wall.map_x = (int)player->pos_x;
	ray_wall.map_y = (int)player->pos_y;
	ray_inter_wall_bis(&ray_wall, player);
	while (game->map[ray_wall.map_x][ray_wall.map_y] != '1')
	{
		if (ray_wall.map_x == (int)enemie->sprite_x
			&& ray_wall.map_y == (int)enemie->sprite_y)
			return (0);
		if (ray_wall.side_dist_x < ray_wall.side_dist_y)
		{
			ray_wall.side_dist_x += fabs(1 / ray_wall.ray_dir_x);
			ray_wall.map_x += ray_wall.step_x;
		}
		else
		{
			ray_wall.side_dist_y += fabs(1 / ray_wall.ray_dir_y);
			ray_wall.map_y += ray_wall.step_y;
		}
	}
	return (1);
}

double	calculate_distance(double x1, double y1, double x2, double y2)
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
