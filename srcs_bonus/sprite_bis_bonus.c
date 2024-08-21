/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite_bis_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acasanov <acasanov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 17:51:22 by acasanov          #+#    #+#             */
/*   Updated: 2024/08/21 18:38:45 by acasanov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

int	ennemy_or_opponent(t_game *game, t_player *player,
	t_player *opponent, int begin)
{
	if (game->var.dist3 > game->var.dist2 && game->var.dist3
		< game->var.old_dist && game->var.dist3 > game->var.dist1)
	{
		draw_opponent(game, opponent, player, begin);
		game->var.dist3 = 0;
		return (1);
	}
	else if (game->var.enemi_index < game->enemies_count && game->var.dist1
		> game->var.dist2 && game->var.dist1 < game->var.old_dist)
	{
		draw_ennemies(game, game->enemies[game->var.enemi_index]
			->sprite, player, begin);
		game->var.enemi_index++;
		if (game->var.enemi_index < game->enemies_count)
			game->var.dist1 = sqrt(pow(game->enemies[game->var.enemi_index]
						->sprite->sprite_x - player->pos_x, 2) + pow(game
						->enemies[game->var.enemi_index]->sprite->sprite_y
						- player->pos_y, 2));
		else
			game->var.dist1 = 0;
		return (1);
	}
	return (0);
}

void	init_draw_var(t_game *game, t_player *player,
	t_player **opponent, int begin)
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
		game->var.dist3 = sqrt(pow((*opponent)->pos_x - player->pos_x, 2)
				+ pow((*opponent)->pos_y - player->pos_y, 2));
	if (game->enemies_count > 0)
		game->var.dist1 = sqrt(pow(game->enemies[game->var.enemi_index]
					->sprite->sprite_x - player->pos_x, 2)
				+ pow(game->enemies[game->var.enemi_index]
					->sprite->sprite_y - player->pos_y, 2));
}

void	draw_sprite_two(t_game *game, t_player *player,
	t_player *opponent, int begin)
{
	while (game->var.enemi_index < game->enemies_count)
	{
		if (game->var.dist3 != 0 && game->var.dist3 > game->var.dist1)
		{
			draw_opponent(game, opponent, player, begin);
			game->var.dist3 = 0;
		}
		draw_ennemies(game, game->enemies[game->var.enemi_index]
			->sprite, player, begin);
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
