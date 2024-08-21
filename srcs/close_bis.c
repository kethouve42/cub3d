/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close_bis.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acasanov <acasanov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 15:31:00 by acasanov          #+#    #+#             */
/*   Updated: 2024/08/21 16:14:12 by acasanov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	free_sprite(t_game *game)
{
	int	i;

	i = 0;
	while (i < game->graphics->sprite_count)
	{
		free(game->graphics->sprites[i]->s_tex);
		free(game->graphics->sprites[i]);
		i++;
	}
}

void	free_enemie(t_game *game)
{
	int	i;
	int	j;

	i = 0;
	while (i < game->enemies_count)
	{
		j = 0;
		free(game->enemies[i]->sprite->s_tex);
		free(game->enemies[i]->sprite);
		free(game->enemies[i]);
		i++;
	}
	free(game->enemies);
}

void	free_player(t_game *game)
{
	free(game->player->sprite->s_tex);
	free(game->player->sprite);
	free(game->player);
	free(game->player_two->sprite->s_tex);
	free(game->player_two->sprite);
	free(game->player_two);
}
