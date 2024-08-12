/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acasanov <acasanov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 17:24:51 by acasanov          #+#    #+#             */
/*   Updated: 2024/08/12 17:59:54 by acasanov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/* ============================== KEY VALUES ================================ */
/* 65307 = escape	|	65363 = right arrow	 |	65361 = left arrow			  */
/* 119 = W	|	122 = Z	 |	115 = S	 |	100 = D	 |	97 = A	 |	 113 = Q      */
/* 101 = E																	  */
/* ========================================================================== */

/* Changes to 1 the keys pressed */
int	key_press(int keycode, t_game *game)
{
	if (keycode == 65307)
		close_game(game, NULL);
	if (keycode == 65363)
		game->key->rotate_right = 1;
	if (keycode == 65361)
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
		shoot(game);
	if (keycode == 101)
		open_door(game, (int)game->player->pos_x,
			(int)game->player->pos_y, game->map);
	return (0);
}

/* Changes to 0 the keys released */
int	key_release(int keycode, t_game *game)
{
	if (keycode == 65363)
		game->key->rotate_right = 0;
	if (keycode == 65361)
		game->key->rotate_left = 0;
	if (keycode == 119 || keycode == 122)
		game->key->forward = 0;
	if (keycode == 115)
		game->key->back = 0;
	if (keycode == 100)
		game->key->right = 0;
	if (keycode == 97 || keycode == 113)
		game->key->left = 0;
	if (keycode == 32)
		game->key->shoot = 0;
	return (0);
}

/* Moves the player vertically if there is no wall */
void	player_forward_back(t_game *game, double speed, int temp_x, int temp_y)
{
	if (game->key->forward)
	{
		temp_x = (int)(game->player->pos_x + game->player->dir_x
				* speed * HITBOX_SIZE);
		temp_y = (int)(game->player->pos_y + game->player->dir_y
				* speed * HITBOX_SIZE);
		if (is_into_str(game->map[temp_x][temp_y], "1DPB") == 0 && is_into_str(game->map[temp_x][temp_y], "d") != 1)
		{
			game->player->pos_x += game->player->dir_x * speed;
			game->player->pos_y += game->player->dir_y * speed;
		}
		if (is_into_str(game->map[temp_x][temp_y], "d") == 1) // a appliquer aux 4 directions
		{
			if(game->player->pos_x - temp_x < 0.7 && game->player->pos_x - temp_x > 0.3)
			{
				game->player->pos_x += game->player->dir_x * speed;
				game->player->pos_y += game->player->dir_y * speed;
			}
		}
	}
	if (game->key->back)
	{
		temp_x = (int)(game->player->pos_x - game->player->dir_x
				* speed * HITBOX_SIZE);
		temp_y = (int)(game->player->pos_y - game->player->dir_y
				* speed * HITBOX_SIZE);
		if (is_into_str(game->map[temp_x][temp_y], "1DPB") == 0)
		{
			game->player->pos_x -= game->player->dir_x * speed;
			game->player->pos_y -= game->player->dir_y * speed;
		}
	}
}

/* Moves the player horizontally if there is no wall */
void	player_right_left(t_game *game, double speed, int temp_x, int temp_y)
{
	if (game->key->right)
	{
		temp_x = (int)(game->player->pos_x + game->player->dir_y
				* speed * HITBOX_SIZE);
		temp_y = (int)(game->player->pos_y - game->player->dir_x
				* speed * HITBOX_SIZE);
		if (is_into_str(game->map[temp_x][temp_y], "1DPB") == 0)
		{
			game->player->pos_x += game->player->dir_y * speed;
			game->player->pos_y -= game->player->dir_x * speed;
		}
	}
	if (game->key->left)
	{
		temp_x = (int)(game->player->pos_x - game->player->dir_y
				* speed * HITBOX_SIZE);
		temp_y = (int)(game->player->pos_y + game->player->dir_x
				* speed * HITBOX_SIZE);
		if (is_into_str(game->map[temp_x][temp_y], "1DPB") == 0)
		{
			game->player->pos_x -= game->player->dir_y * speed;
			game->player->pos_y += game->player->dir_x * speed;
		}
	}
}

/* Update player placements and display
   The speed is divided by 2 in case of diagonal movement */
int	player(t_game *game)
{
	int		temp_x;
	int		temp_y;

	if (game->key->left + game->key->right == 1)
		player_forward_back(game, MOVE_SPEED / 2, temp_x, temp_y);
	else
		player_forward_back(game, MOVE_SPEED, temp_x, temp_y);
	if (game->key->forward + game->key->back == 1)
		player_right_left(game, MOVE_SPEED / 2, temp_x, temp_y);
	else
		player_right_left(game, MOVE_SPEED, temp_x, temp_y);
	draw_skyground(game);
	raycast(game);
	minimap(game);
	mlx_put_image_to_window(game->mlx, game->mlx_win, game->img->img, 0, 0);
	update_all_sprites_index(game);
	return (0);
}
