/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close_bis_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kethouve <kethouve@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 15:31:00 by acasanov          #+#    #+#             */
/*   Updated: 2024/08/23 15:53:17 by kethouve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

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

void	free_player_img(t_game *game)
{
	if (game->graphics->s_pl_face1.img)
		mlx_destroy_image(game->mlx, game->graphics->s_pl_face1.img);
	if (game->graphics->s_pl_face2.img)
		mlx_destroy_image(game->mlx, game->graphics->s_pl_face2.img);
	if (game->graphics->s_pl_back1.img)
		mlx_destroy_image(game->mlx, game->graphics->s_pl_back1.img);
	if (game->graphics->s_pl_back2.img)
		mlx_destroy_image(game->mlx, game->graphics->s_pl_back2.img);
	if (game->graphics->s_pl_left1.img)
		mlx_destroy_image(game->mlx, game->graphics->s_pl_left1.img);
	if (game->graphics->s_pl_left2.img)
		mlx_destroy_image(game->mlx, game->graphics->s_pl_left2.img);
	if (game->graphics->s_pl_right1.img)
		mlx_destroy_image(game->mlx, game->graphics->s_pl_right1.img);
	if (game->graphics->s_pl_right2.img)
		mlx_destroy_image(game->mlx, game->graphics->s_pl_right2.img);
}
