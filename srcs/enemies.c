/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enemies.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kethouve <kethouve@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 15:26:08 by kethouve          #+#    #+#             */
/*   Updated: 2024/08/02 21:13:09 by kethouve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	chase(t_game *game)
{
	if (game->enemies.sprite->sprite_x > game->player->pos_x)
		game->enemies.sprite->sprite_x -= 0.05;
	if (game->enemies.sprite->sprite_x < game->player->pos_x)
		game->enemies.sprite->sprite_x += 0.05;
	if (game->enemies.sprite->sprite_y < game->player->pos_y)
		game->enemies.sprite->sprite_y += 0.05;
	if (game->enemies.sprite->sprite_y > game->player->pos_y)
		game->enemies.sprite->sprite_y -= 0.05;
	
}

void	detection(t_game *game)
{
	if (game->enemies.sprite->sprite_x - game->player->pos_x <= 1
		&& game->enemies.sprite->sprite_x - game->player->pos_x >= -1)
	{
		if (game->enemies.sprite->sprite_y - game->player->pos_y <= 1
			&& game->enemies.sprite->sprite_y - game->player->pos_y >= -1)
		{
			printf("CHASE_ON\n");
			game->enemies.chase_status = 1;
		}
	}
			/*printf("game->enemies.sprite->sprite_x - game->player->pos_x: %f\n", game->enemies.sprite->sprite_x - game->player->pos_x);
			printf("game->enemies.sprite->sprite_y - game->player->pos_y: %f\n", game->enemies.sprite->sprite_y - game->player->pos_y);
			printf("game->player->pos_x - game->enemies.sprite->sprite_x: %f\n", game->player->pos_x - game->enemies.sprite->sprite_x);
			printf("game->player->pos_y - game->enemies.sprite->sprite_y: %f\n", game->player->pos_y - game->enemies.sprite->sprite_y);
			printf("player x:%f | y:%f || ennemy: x:%f | y:%f\n", game->enemies.sprite->sprite_y, game->enemies.sprite->sprite_x, game->player->pos_y, game->player->pos_x);*/
}

void	move_enemies(t_game *game)
{
	if (game->enemies.chase_status == 1)
		chase(game);
	else
	{
		if (game->enemies.move_state == 2)
			game->enemies.sprite->sprite_y -= 0.05;
		if (game->enemies.move_state == 4)
			game->enemies.sprite->sprite_y += 0.05;
		if (game->enemies.move_state == 1)
			game->enemies.sprite->sprite_x -= 0.05;
		if (game->enemies.move_state == 3)
			game->enemies.sprite->sprite_x += 0.05;
		game->enemies.move--;
		if (game->enemies.move == 0)
		{
			game->enemies.move = game->enemies.n_move;
			if (game->enemies.move_state == 1)
				game->enemies.move_state = 2;
			else if (game->enemies.move_state == 2)
				game->enemies.move_state = 3;
			else if (game->enemies.move_state == 3)
				game->enemies.move_state = 4;
			else
				game->enemies.move_state = 1;
		}
		detection(game);
	}
	if ((game->enemies.sprite->sprite_x - game->player->pos_x <= 0.1
		&& game->enemies.sprite->sprite_x - game->player->pos_x >= -0.1)
		&& (game->enemies.sprite->sprite_y - game->player->pos_y <= 0.1
		&& game->enemies.sprite->sprite_y - game->player->pos_y >= -0.1)) // a ameliorer
	{
		printf("game over\n");
		close_game(game, NULL);
	}
}
