/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time_system.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acasanov <acasanov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 16:25:22 by acasanov          #+#    #+#             */
/*   Updated: 2024/08/20 18:33:52 by acasanov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	update_enemies(t_game *game)
{
	int	i;

	i = 0;
	while (i < game->enemies_count)
	{
		if (game->enemies[i]->hp > 0)
		{
			game->enemies[i]->sprite->index++;
			if (game->enemies[i]->sprite->index
				>= game->enemies[i]->sprite->nb - 1)
				game->enemies[i]->sprite->index = 0;
		}
		i++;
	}
}

void	update_sprite(t_game *game)
{
	int	i;

	i = 0;
	while (i < game->graphics->sprite_count)
	{
		game->graphics->sprites[i]->index++;
		if (game->graphics->sprites[i]->index >= game->graphics->sprites[i]->nb)
			game->graphics->sprites[i]->index = 0;
		i++;
	}
}

void	update_sprite_index(t_game *game, t_texture *tex)
{
	tex->index++;
	if (tex->index >= tex->nb)
		tex->index = 0;
}

void	update_all_sprites_index(t_game *game)
{
	int	i;

	i = 0;
	if (get_current_time() - game->last_ennemi_time_update > 35)
	{
		while (i < game->enemies_count)
		{
			if (game->enemies[i]->hp > 0)
				move_enemies(game, game->enemies[i]);
			i++;
		}
		game->last_ennemi_time_update = get_current_time();
	}
	if (get_current_time() - game->last_time_update > SPRITE_UPDATE)
	{
		update_sprite_index(game, &game->graphics->tex_n);
		update_sprite_index(game, &game->graphics->tex_s);
		update_sprite_index(game, &game->graphics->tex_e);
		update_sprite_index(game, &game->graphics->tex_w);
		update_enemies(game);
		update_sprite(game);
		game->last_time_update = get_current_time();
	}
}

int	get_current_time(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) == -1)
		write(2, "gettimeofday() error\n", 22);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}
