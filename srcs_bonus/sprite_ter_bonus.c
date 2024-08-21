/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite_ter_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acasanov <acasanov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 16:14:51 by acasanov          #+#    #+#             */
/*   Updated: 2024/08/21 18:38:54 by acasanov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	draw_sprite_part_one_bis(t_game *game, t_ray_tex *ray_tex,
	t_sprite *sprite, t_player *player)
{
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

void	draw_sprite_part_one(t_game *game, t_ray_tex *ray_tex,
	t_sprite *sprite, t_player *player)
{
	ray_tex->sprite_x = sprite->sprite_x - player->pos_x;
	ray_tex->sprite_y = sprite->sprite_y - player->pos_y;
	ray_tex->inv_det = 1.0 / (player->plane_x * player->dir_y
			- player->dir_x * player->plane_y);
	ray_tex->transform_x = ray_tex->inv_det * (player->dir_y
			* ray_tex->sprite_x - player->dir_x * ray_tex->sprite_y);
	ray_tex->transform_y = ray_tex->inv_det * (-player->plane_y
			* ray_tex->sprite_x + player->plane_x * ray_tex->sprite_y);
	if (game->gamemode == 2)
		ray_tex->sprite_screen_x = (int)
			(((game->graphics->screen_lenght / 2 - 5) / 2)
				* (1 + ray_tex->transform_x / ray_tex->transform_y));
	else
		ray_tex->sprite_screen_x = (int)((game->graphics->screen_lenght / 2)
				* (1 + ray_tex->transform_x / ray_tex->transform_y));
	draw_sprite_part_one_bis(game, ray_tex, sprite, player);
}

void	draw_sprite_part_three(t_game *game, t_ray_tex *ray_tex,
	t_img *tex, int begin)
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
		if (ray_tex->color != 0x00FFFFFF)
			my_mlx_pixel_put(game->img, ray_tex->y, ray_tex->stripe
				+ begin, ray_tex->color);
		ray_tex->y++;
	}
}

void	draw_sprite_part_two_bis(t_game *game, t_ray_tex *ray_tex,
	t_img *tex, int begin)
{
	int		screen_lenght;

	if (game->gamemode == 2)
		screen_lenght = game->graphics->screen_lenght / 2 - 5;
	else
		screen_lenght = game->graphics->screen_lenght;
	while (ray_tex->stripe < ray_tex->draw_end_x)
	{
		ray_tex->tex_x = (int)(256 * (ray_tex->stripe
					- (-ray_tex->sprite_width / 2 + ray_tex->sprite_screen_x))
				* tex->width / ray_tex->sprite_width) / 256;
		if (ray_tex->transform_y > 0 && ray_tex->stripe > 0 && ray_tex->stripe
			< screen_lenght && ray_tex->transform_y
			< game->z_buffer[ray_tex->stripe + begin])
		{
			draw_sprite_part_three(game, ray_tex, tex, begin);
		}
		ray_tex->stripe++;
	}
}

void	draw_sprite_part_two(t_game *game, t_ray_tex *ray_tex,
	t_img *tex, int begin)
{
	int		screen_lenght;

	if (game->gamemode == 2)
		screen_lenght = game->graphics->screen_lenght / 2 - 5;
	else
		screen_lenght = game->graphics->screen_lenght;
	ray_tex->draw_start_x = -ray_tex->sprite_width
		/ 2 + ray_tex->sprite_screen_x;
	if (ray_tex->draw_start_x < 0)
		ray_tex->draw_start_x = 0;
	ray_tex->draw_end_x = ray_tex->sprite_width / 2 + ray_tex->sprite_screen_x;
	if (ray_tex->draw_end_x >= screen_lenght)
		ray_tex->draw_end_x = screen_lenght - 1;
	ray_tex->stripe = ray_tex->draw_start_x;
	draw_sprite_part_two_bis(game, ray_tex, tex, begin);
}
