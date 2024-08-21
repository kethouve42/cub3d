/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_movement_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acasanov <acasanov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 15:59:51 by acasanov          #+#    #+#             */
/*   Updated: 2024/08/21 18:38:15 by acasanov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	player_back(t_game *game, double speed, t_player *player, t_key *key)
{
	int	temp_x;
	int	temp_y;

	if (key->back)
	{
		temp_x = (int)(player->pos_x - player->dir_x
				* speed * HITBOX_SIZE);
		temp_y = (int)(player->pos_y - player->dir_y
				* speed * HITBOX_SIZE);
		if (is_into_str(game->map[temp_x][temp_y], "1DPB") == 0)
		{
			player->pos_x -= player->dir_x * speed;
			player->pos_y -= player->dir_y * speed;
		}
		player->sprite->sprite_x = player->pos_x;
		player->sprite->sprite_y = player->pos_y;
	}
}

/* Moves the player vertically if there is no wall */
void	player_forward_back(t_game *game, double speed,
	t_player *player, t_key *key)
{
	int	temp_x;
	int	temp_y;

	if (key->forward)
	{
		temp_x = (int)(player->pos_x + player->dir_x
				* speed * HITBOX_SIZE);
		temp_y = (int)(player->pos_y + player->dir_y
				* speed * HITBOX_SIZE);
		if (is_into_str(game->map[temp_x][temp_y], "1DPB") == 0)
		{
			player->pos_x += player->dir_x * speed;
			player->pos_y += player->dir_y * speed;
		}
		player->sprite->sprite_x = player->pos_x;
		player->sprite->sprite_y = player->pos_y;
	}
	player_back(game, speed, player, key);
}

void	player_left(t_game *game, double speed, t_player *player, t_key *key)
{
	int	temp_x;
	int	temp_y;

	if (key->left)
	{
		temp_x = (int)(player->pos_x - player->dir_y
				* speed * HITBOX_SIZE);
		temp_y = (int)(player->pos_y + player->dir_x
				* speed * HITBOX_SIZE);
		if (is_into_str(game->map[temp_x][temp_y], "1DPB") == 0)
		{
			player->pos_x -= player->dir_y * speed;
			player->pos_y += player->dir_x * speed;
		}
		player->sprite->sprite_x = player->pos_x;
		player->sprite->sprite_y = player->pos_y;
	}
}

/* Moves the player horizontally if there is no wall */
void	player_right_left(t_game *game, double speed,
	t_player *player, t_key *key)
{
	int	temp_x;
	int	temp_y;

	if (key->right)
	{
		temp_x = (int)(player->pos_x + player->dir_y
				* speed * HITBOX_SIZE);
		temp_y = (int)(player->pos_y - player->dir_x
				* speed * HITBOX_SIZE);
		if (is_into_str(game->map[temp_x][temp_y], "1DPB") == 0)
		{
			player->pos_x += player->dir_y * speed;
			player->pos_y -= player->dir_x * speed;
		}
		player->sprite->sprite_x = player->pos_x;
		player->sprite->sprite_y = player->pos_y;
	}
	player_left(game, speed, player, key);
}

/* Rotate player by changing dir and plane */
void	player_rotation(double old_dir_x, double old_plane_x,
	t_player *player, t_key *key)
{
	if (key->rotate_right && !key->rotate_left)
	{
		player->dir_x = player->dir_x * cos(-ROT_SPEED)
			- player->dir_y * sin(-ROT_SPEED);
		player->dir_y = old_dir_x * sin(-ROT_SPEED)
			+ player->dir_y * cos(-ROT_SPEED);
		player->plane_x = player->plane_x * cos(-ROT_SPEED)
			- player->plane_y * sin(-ROT_SPEED);
		player->plane_y = old_plane_x * sin(-ROT_SPEED)
			+ player->plane_y * cos(-ROT_SPEED);
	}
	else if (key->rotate_left && !key->rotate_right)
	{
		player->dir_x = player->dir_x * cos(ROT_SPEED)
			- player->dir_y * sin(ROT_SPEED);
		player->dir_y = old_dir_x * sin(ROT_SPEED)
			+ player->dir_y * cos(ROT_SPEED);
		player->plane_x = player->plane_x * cos(ROT_SPEED)
			- player->plane_y * sin(ROT_SPEED);
		player->plane_y = old_plane_x * sin(ROT_SPEED)
			+ player->plane_y * cos(ROT_SPEED);
	}
}
