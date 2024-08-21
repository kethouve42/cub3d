/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acasanov <acasanov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 17:24:51 by acasanov          #+#    #+#             */
/*   Updated: 2024/08/21 18:38:11 by acasanov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

/* ============================== KEY VALUES ================================ */
/* 65307 = escape	|	65363 = right arrow	 |	65361 = left arrow			  */
/* 119 = W	|	122 = Z	 |	115 = S	 |	100 = D	 |	97 = A	 |	 113 = Q      */
/* 101 = E																	  */
/* ========================================================================== */

void	key_press_two(int keycode, t_game *game)
{
	if (keycode == 65432)
		game->key2->rotate_right = 1;
	if (keycode == 65430)
		game->key2->rotate_left = 1;
	if (keycode == 65362)
		game->key2->forward = 1;
	if (keycode == 65364)
		game->key2->back = 1;
	if (keycode == 65363)
		game->key2->right = 1;
	if (keycode == 65361)
		game->key2->left = 1;
	if (keycode == 65438)
		shoot(game, game->player_two, 2);
	if (keycode == 65431)
		open_door(game, (int)game->player_two->pos_x,
			(int)game->player_two->pos_y, game->map);
}

/* Changes to 1 the keys pressed */
int	key_press(int keycode, t_game *game)
{
	if (keycode == 65307)
		close_game(game, NULL);
	if (keycode == 108)
		game->key->rotate_right = 1;
	if (keycode == 107)
		game->key->rotate_left = 1;
	if (keycode == 119 || keycode == 122)
		game->key->forward = 1;
	if (keycode == 115)
		game->key->back = 1;
	if (keycode == 100)
		game->key->right = 1;
	if (keycode == 97 || keycode == 113)
		game->key->left = 1;
	if (keycode == 32)
		shoot(game, game->player, 1);
	if (keycode == 101)
		open_door(game, (int)game->player->pos_x,
			(int)game->player->pos_y, game->map);
	if (game->gamemode == 2)
		key_press_two(keycode, game);
	return (0);
}

/* Changes to 0 the keys released */
int	key_release(int keycode, t_game *game)
{
	if (keycode == 108)
		game->key->rotate_right = 0;
	if (keycode == 107)
		game->key->rotate_left = 0;
	if (keycode == 119 || keycode == 122)
		game->key->forward = 0;
	if (keycode == 115)
		game->key->back = 0;
	if (keycode == 100)
		game->key->right = 0;
	if (keycode == 97 || keycode == 113)
		game->key->left = 0;
	if (keycode == 65432)
		game->key2->rotate_right = 0;
	if (keycode == 65430)
		game->key2->rotate_left = 0;
	if (keycode == 65362)
		game->key2->forward = 0;
	if (keycode == 65364)
		game->key2->back = 0;
	if (keycode == 65363)
		game->key2->right = 0;
	if (keycode == 65361)
		game->key2->left = 0;
	return (0);
}

void	player_two(t_game *game)
{
	if (game->key2->left + game->key2->right == 1)
		player_forward_back(game, MOVE_SPEED / 2,
			game->player_two, game->key2);
	else
		player_forward_back(game, MOVE_SPEED, game->player_two, game->key2);
	if (game->key2->forward + game->key2->back == 1)
		player_right_left(game, MOVE_SPEED / 2, game->player_two, game->key2);
	else
		player_right_left(game, MOVE_SPEED, game->player_two, game->key2);
	player_rotation(game->player_two->dir_x, game->player_two->plane_x,
		game->player_two, game->key2);
}

/* Update player placements and display
   The speed is divided by 2 in case of diagonal movement */
int	player(t_game *game)
{
	if (game->key->left + game->key->right == 1)
		player_forward_back(game, MOVE_SPEED / 2, game->player, game->key);
	else
		player_forward_back(game, MOVE_SPEED, game->player, game->key);
	if (game->key->forward + game->key->back == 1)
		player_right_left(game, MOVE_SPEED / 2, game->player, game->key);
	else
		player_right_left(game, MOVE_SPEED, game->player, game->key);
	player_rotation(game->player->dir_x, game->player->plane_x,
		game->player, game->key);
	if (game->gamemode == 2)
		player_two(game);
	update_graphics(game);
	return (0);
}
