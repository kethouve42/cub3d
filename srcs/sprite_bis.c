/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite_bis.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kethouve <kethouve@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 17:51:22 by acasanov          #+#    #+#             */
/*   Updated: 2024/07/30 17:02:26 by kethouve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_sprite_part_one(t_game *game, t_ray_tex *ray_tex, t_sprite *sprite)
{
	ray_tex->sprite_x = sprite->x - game->player->pos_x;
	ray_tex->sprite_y = sprite->y - game->player->pos_y;
	ray_tex->inv_det = 1.0 / (game->player->plane_x * game->player->dir_y
			- game->player->dir_x * game->player->plane_y);
	ray_tex->transform_x = ray_tex->inv_det * (game->player->dir_y
			* ray_tex->sprite_x - game->player->dir_x * ray_tex->sprite_y);
	ray_tex->transform_y = ray_tex->inv_det * (-game->player->plane_y
			* ray_tex->sprite_x + game->player->plane_x * ray_tex->sprite_y);
	ray_tex->sprite_screen_x = (int)((game->graphics->screen_lenght / 2)
			* (1 + ray_tex->transform_x / ray_tex->transform_y));
	ray_tex->sprite_height = abs((int)(game->graphics->screen_height
				/ ray_tex->transform_y)) / 1;
	ray_tex->draw_start_y = -ray_tex->sprite_height / 2
		+ game->graphics->screen_height / 2;
	if (ray_tex->draw_start_y < 0)
		ray_tex->draw_start_y = 0;
	ray_tex->draw_end_y = ray_tex->sprite_height / 2
		+ game->graphics->screen_height / 2;
	if (ray_tex->draw_end_y >= game->graphics->screen_height)
		ray_tex->draw_end_y = game->graphics->screen_height - 1;
	ray_tex->sprite_width = abs((int)(game->graphics->screen_height
				/ ray_tex->transform_y)) / 1;
}

void	draw_sprite_part_three(t_game *game, t_ray_tex *ray_tex, t_img *tex)
{
	ray_tex->y = ray_tex->draw_start_y;
	while (ray_tex->y < ray_tex->draw_end_y)
	{
		ray_tex->d = (ray_tex->y) * 256 - game->graphics->screen_height
			* 128 + ray_tex->sprite_height * 128;
		ray_tex->tex_y = ((ray_tex->d * tex->height)
				/ ray_tex->sprite_height) / 256;
		ray_tex->color = tex->data[ray_tex->tex_y
			* tex->width + ray_tex->tex_x];
		if (ray_tex->color & 0x00FFFFFF)
			my_mlx_pixel_put(game->img, ray_tex->y,
				ray_tex->stripe, ray_tex->color);
		ray_tex->y++;
	}
}

void	draw_sprite_part_two(t_game *game, t_ray_tex *ray_tex, t_img *tex)
{
	ray_tex->draw_start_x = -ray_tex->sprite_width
		/ 2 + ray_tex->sprite_screen_x;
	if (ray_tex->draw_start_x < 0)
		ray_tex->draw_start_x = 0;
	ray_tex->draw_end_x = ray_tex->sprite_width / 2 + ray_tex->sprite_screen_x;
	if (ray_tex->draw_end_x >= game->graphics->screen_lenght)
		ray_tex->draw_end_x = game->graphics->screen_lenght - 1;
	ray_tex->stripe = ray_tex->draw_start_x;
	while (ray_tex->stripe < ray_tex->draw_end_x)
	{
		ray_tex->tex_x = (int)(256 * (ray_tex->stripe
					- (-ray_tex->sprite_width / 2 + ray_tex->sprite_screen_x))
				* tex->width / ray_tex->sprite_width) / 256;
		if (ray_tex->transform_y > 0 && ray_tex->stripe > 0 && ray_tex->stripe
			< game->graphics->screen_lenght && ray_tex->transform_y
			< game->z_buffer[ray_tex->stripe])
		{
			draw_sprite_part_three(game, ray_tex, tex);
		}
		ray_tex->stripe++;
	}
}

void	draw_sprite(t_game *game)
{
	t_img		*tex;
	t_ray_tex	ray_tex;
	t_sprite	*sprite;
	int			i;

	i = 0;
	while (i < game->graphics->sprite_count)
	{
		sprite = &game->graphics->sprites[i];
		tex = &sprite->s_tex;
		draw_sprite_part_one(game, &ray_tex, sprite);
		draw_sprite_part_two(game, &ray_tex, tex);
		i++;
	}
}
