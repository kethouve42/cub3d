/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shoot.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kethouve <kethouve@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 17:53:09 by kethouve          #+#    #+#             */
/*   Updated: 2024/07/30 18:10:16 by kethouve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_cursor(t_game *game)
{
	int	y;
	int	x;
	int	y_start;
	int	x_start;

	y_start = (game->graphics->screen_height / 2) - 10;
	x_start = (game->graphics->screen_lenght / 2);
	y = 0;
	x = -3;
	while (y <  20)
	{
		while (x < 4)
		{
			my_mlx_pixel_put(game->img, y_start + y, x_start + x, 0x000000);
			x++;
		}
		x = -3;
		y++;
	}
	y_start = (game->graphics->screen_height / 2);
	x_start = (game->graphics->screen_lenght / 2) - 10;
	y = -3;
	x = 0;
	while (x < 20)
	{
		while (y < 4)
		{
			my_mlx_pixel_put(game->img, y_start + y, x_start + x, 0x000000);
			y++;
		}
		y = -3;
		x++;
	}
	my_mlx_pixel_put(game->img, y_start, game->graphics->screen_lenght / 2, 0x555555);
}

void	shoot(t_game *game)
{
	// Vérifier si le joueur tire
    if (check_shot(game, game->ennemie, 1))
    {
		printf("Tir réussi!\n");
           // Logique pour supprimer ou marquer l'ennemi comme touché
	}
	else
	{
		printf("Tir manqué!\n");
	}
}

void    draw_ennemies(t_game *game, t_sprite ennemie)
{
	t_img		*tex;
	t_ray_tex	ray_tex;
	t_sprite	*sprite;

	sprite = &game->ennemie;
	tex = &sprite->s_tex;
	draw_sprite_part_one(game, &ray_tex, sprite);
	draw_sprite_part_two(game, &ray_tex, tex);
}

int ray_intersects_wall(t_game *game, double ray_dir_x, double ray_dir_y, double target_x, double target_y)
{
    int map_x = (int)game->player->pos_x;
    int map_y = (int)game->player->pos_y;

    double delta_dist_x = fabs(1 / ray_dir_x);
    double delta_dist_y = fabs(1 / ray_dir_y);
    double side_dist_x;
    double side_dist_y;
    int step_x;
    int step_y;
    int hit = 0;

    if (ray_dir_x < 0)
    {
        step_x = -1;
        side_dist_x = (game->player->pos_x - map_x) * delta_dist_x;
    }
    else
    {
        step_x = 1;
        side_dist_x = (map_x + 1.0 - game->player->pos_x) * delta_dist_x;
    }

    if (ray_dir_y < 0)
    {
        step_y = -1;
        side_dist_y = (game->player->pos_y - map_y) * delta_dist_y;
    }
    else
    {
        step_y = 1;
        side_dist_y = (map_y + 1.0 - game->player->pos_y) * delta_dist_y;
    }
    while (hit == 0)
    {
        if (side_dist_x < side_dist_y)
        {
            side_dist_x += delta_dist_x;
            map_x += step_x;
        }
        else
        {
            side_dist_y += delta_dist_y;
            map_y += step_y;
        }
        if (game->map[map_x][map_y] == '1')
        {
            hit = 1;
        }
        if (map_x == (int)target_x && map_y == (int)target_y)
        {
            return 0; // Pas d'intersection avec un mur
        }
    }
    return 1; // Intersection avec un mur
}

double calculate_distance(double x1, double y1, double x2, double y2)
{
    return sqrt((x2 - x1) * (x2 - y1) + (y2 - y1) * (y2 - y1));
}

double calculate_angle(double dir_x1, double dir_y1, double dir_x2, double dir_y2)
{
    double dot = dir_x1 * dir_x2 + dir_y1 * dir_y2;
    double det = dir_x1 * dir_y2 - dir_y1 * dir_x2;
    return fabs(atan2(det, dot));
}

int check_shot(t_game *game, t_sprite enemies, int num_enemies)
{
    int hit = 0;
    double max_shot_angle = 0.05; // environ 5.7 degrés
    double max_shot_distance = 10.0; // Distance maximale de tir

    for (int i = 0; i < num_enemies; i++)
    {
        double enemy_dir_x = enemies.x - game->player->pos_x;
        double enemy_dir_y = enemies.y - game->player->pos_y;
        double distance_to_enemy = calculate_distance(game->player->pos_x, game->player->pos_y, enemies.x, enemies.y);

        if (distance_to_enemy <= max_shot_distance)
        {
            double shot_angle = calculate_angle(game->player->dir_x, game->player->dir_y, enemy_dir_x, enemy_dir_y);

            if (shot_angle <= max_shot_angle)
            {
                if (!ray_intersects_wall(game, enemy_dir_x, enemy_dir_y, enemies.x, enemies.y))
                {
                    hit = 1; // Tir réussi
                    break;
                }
            }
        }
    }

    return hit;
}


