/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite_bis.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acasanov <acasanov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 17:51:22 by acasanov          #+#    #+#             */
/*   Updated: 2024/08/20 17:25:53 by acasanov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_sprite_part_one(t_game *game, t_ray_tex *ray_tex, t_sprite *sprite, t_player *player)
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
		ray_tex->sprite_screen_x = (int)(((game->graphics->screen_lenght / 2 - 5) / 2) * (1 + ray_tex->transform_x / ray_tex->transform_y));
	else
		ray_tex->sprite_screen_x = (int)((game->graphics->screen_lenght / 2) * (1 + ray_tex->transform_x / ray_tex->transform_y));
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

void	draw_sprite_part_three(t_game *game, t_ray_tex *ray_tex, t_img *tex, int begin)
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
			my_mlx_pixel_put(game->img, ray_tex->y, ray_tex->stripe + begin, ray_tex->color);
		ray_tex->y++;
	}
}

void	draw_sprite_part_two(t_game *game, t_ray_tex *ray_tex, t_img *tex, int begin)
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

int	ennemy_or_opponent(t_game *game, t_player *player, t_player *opponent, int begin)
{
	int	drawed;

	drawed = 0;
	if (game->var.dist3 > game->var.dist2 && game->var.dist3 < game->var.old_dist && game->var.dist3 > game->var.dist1)
	{
		draw_opponent(game, opponent, player, begin);
		game->var.dist3 = 0;
		drawed = 1;
	}
	else if (game->var.enemi_index < game->enemies_count && game->var.dist1 > game->var.dist2 && game->var.dist1 < game->var.old_dist)
	{
		draw_ennemies(game, game->enemies[game->var.enemi_index]->sprite, player, begin);
		game->var.enemi_index++;
		drawed = 1;
		if (game->var.enemi_index < game->enemies_count)
			game->var.dist1 = sqrt(pow(game->enemies[game->var.enemi_index]->sprite->sprite_x - player->pos_x, 2) + pow(game->enemies[game->var.enemi_index]->sprite->sprite_y - player->pos_y, 2));
		else
			game->var.dist1 = 0;
	}
	return (drawed);
}

void	init_draw_var(t_game *game, t_player *player, t_player **opponent, int begin)
{
	game->var.enemi_index = 0;
	game->var.dist3 = 0;
	game->var.i = 0;
	game->var.old_dist = 99;
	game->var.dist1 = 0;
	game->var.dist2 = 0;
	if (game->gamemode == 2 && begin == 0)
		(*opponent) = game->player_two;
	else if (game->gamemode == 2)
		(*opponent) = game->player;
	if (game->gamemode == 2)
		game->var.dist3 = sqrt(pow((*opponent)->pos_x - player->pos_x, 2) + pow((*opponent)->pos_y - player->pos_y, 2));
	if (game->enemies_count > 0)
		game->var.dist1 = sqrt(pow(game->enemies[game->var.enemi_index]->sprite->sprite_x - player->pos_x, 2) + pow(game->enemies[game->var.enemi_index]->sprite->sprite_y - player->pos_y, 2));
}

void	draw_sprite_two(t_game *game, t_player *player, t_player *opponent, int begin)
{
	while(game->var.enemi_index < game->enemies_count)
	{
		if (game->var.dist3 != 0 && game->var.dist3 > game->var.dist1)
		{
			draw_opponent(game, opponent, player, begin);
			game->var.dist3 = 0;
		}
		draw_ennemies(game, game->enemies[game->var.enemi_index]->sprite, player, begin);
		game->var.enemi_index++;
	}
	if (game->gamemode == 2 && game->var.dist3 != 0)
		draw_opponent(game, opponent, player, begin);
}

void	draw_sprite(t_game *game, t_player *player, int begin)
{
	t_ray_tex			ray_tex;
	t_sprite			*sprite;
	t_player			*opponent;

	init_draw_var(game, player, &opponent, begin);
	while (game->var.i < game->graphics->sprite_count)
	{
		sprite = game->graphics->sprites[game->var.i];
		ray_tex.tex = &sprite->s_tex[sprite->index];
		game->var.dist2 = sqrt(pow(sprite->sprite_x - player->pos_x, 2)
			+ pow(sprite->sprite_y - player->pos_y, 2));
		if (ennemy_or_opponent(game, player, opponent, begin) == 0)
		{
			draw_sprite_part_one(game, &ray_tex, sprite, player);
			draw_sprite_part_two(game, &ray_tex, ray_tex.tex, begin);
			game->var.old_dist = game->var.dist2;
			game->var.i++;
		}
	}
	draw_sprite_two(game, player, opponent, begin);
}
