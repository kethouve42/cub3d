/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acasanov <acasanov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 17:24:51 by acasanov          #+#    #+#             */
/*   Updated: 2024/07/20 18:44:11 by acasanov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/* Changes to 1 the keys pressed */
int	key_press(int keycode, t_game *game)
{
	if (keycode == 65307) // Escape key
		close_game(game, NULL);
	if (keycode == 65363) // Right arrow key
		game->key->rotate_right = 1;
	if (keycode == 65361) // Left arrow key
		game->key->rotate_left = 1;
	if (keycode == 119 || keycode == 122) // W/Z key (to the up)
		game->key->forward = 1;
	if (keycode == 115) // S key (to the back)
		game->key->back = 1;
	if (keycode == 100) // D key (to the right)
		game->key->right = 1;
	if (keycode == 97 || keycode == 113) // A/Q key (to the left)
		game->key->left = 1;
	return (0);
}

/* Changes to 0 the keys released */
int	key_release(int keycode, t_game *game)
{
	if (keycode == 65363) // Right arrow key
		game->key->rotate_right = 0;
	if (keycode == 65361) // Left arrow key
		game->key->rotate_left = 0;
	if (keycode == 119 || keycode == 122) // W/Z key (to the up)
		game->key->forward = 0;
	if (keycode == 115) // S key (to the back)
		game->key->back = 0;
	if (keycode == 100) // D key (to the right)
		game->key->right = 0;
	if (keycode == 97 || keycode == 113) // A/Q key (to the left)
		game->key->left = 0;
	return (0);
}

/* Rotate player by changing dir and plane */
void	player_rotation(t_game *game, double old_dir_x, double old_plane_x)
{
	if (game->key->rotate_right && !game->key->rotate_left)
	{
		game->player->dir_x = game->player->dir_x * cos(-ROT_SPEED)
			- game->player->dir_y * sin(-ROT_SPEED);
		game->player->dir_y = old_dir_x * sin(-ROT_SPEED)
			+ game->player->dir_y * cos(-ROT_SPEED);
		game->player->plane_x = game->player->plane_x * cos(-ROT_SPEED)
			- game->player->plane_y * sin(-ROT_SPEED);
		game->player->plane_y = old_plane_x * sin(-ROT_SPEED)
			+ game->player->plane_y * cos(-ROT_SPEED);
	}
	else if (game->key->rotate_left && !game->key->rotate_right)
	{
		game->player->dir_x = game->player->dir_x * cos(ROT_SPEED)
			- game->player->dir_y * sin(ROT_SPEED);
		game->player->dir_y = old_dir_x * sin(ROT_SPEED)
			+ game->player->dir_y * cos(ROT_SPEED);
		game->player->plane_x = game->player->plane_x * cos(ROT_SPEED)
			- game->player->plane_y * sin(ROT_SPEED);
		game->player->plane_y = old_plane_x * sin(ROT_SPEED)
			+ game->player->plane_y * cos(ROT_SPEED);
	}
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
		if (game->map[temp_x][temp_y] == '0')
		{
			game->player->pos_x += game->player->dir_x * speed;
			game->player->pos_y += game->player->dir_y * speed;
		}
	}
	if (game->key->back)
	{
		temp_x = (int)(game->player->pos_x - game->player->dir_x
				* speed * HITBOX_SIZE);
		temp_y = (int)(game->player->pos_y - game->player->dir_y
				* speed * HITBOX_SIZE);
		if (game->map[temp_x][temp_y] == '0')
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
		if (game->map[temp_x][temp_y] == '0')
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
		if (game->map[temp_x][temp_y] == '0')
		{
			game->player->pos_x -= game->player->dir_y * speed;
			game->player->pos_y += game->player->dir_x * speed;
		}
	}
}
