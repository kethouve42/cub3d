/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acasanov <acasanov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 17:24:51 by acasanov          #+#    #+#             */
/*   Updated: 2024/07/24 18:56:44 by acasanov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/* ============================== KEY VALUES ================================ */
/* 65307 = escape	|	65363 = right arrow	 |	65361 = left arrow			  */
/* 119 = W	|	122 = Z	 |	115 = S	 |	100 = D	 |	97 = A	 |	 113 = Q      */
/* 101 = E																	  */
/* ========================================================================== */

void	change_door_state(t_game *game, int x, int y)
{
	if (game->map[y][x] == 'D')
		game->map[y][x] = 'd';
	else if (game->map[y][x] == 'd')
	{
		if ((int)game->player->pos_x != y || (int)game->player->pos_y != x)
			game->map[y][x] = 'D';
		else
			printf("dans la porte\n");
	}
	else
		printf ("Nani ???\n");
	printf("change door [%d:%d] => %c\n", x + 1, y + 1, game->map[y][x]);
}

void	open_door(t_game *game, int y, int x, char **map)
{
	//if (map[y][x] == 'D' || map[y][x] == 'd')
		//change_door_state(game, x, y);
	if (map[y - 1][x] == 'D' || map[y - 1][x] == 'd')
		change_door_state(game, x, y - 1);
	if (map[y - 1][x - 1] == 'D' || map[y - 1][x - 1] == 'd')
		change_door_state(game, x - 1, y - 1);
	if (map[y - 1][x + 1] == 'D' || map[y - 1][x + 1] == 'd')
		change_door_state(game, x + 1, y - 1);
	if (map[y][x - 1] == 'D' || map[y][x - 1] == 'd')
		change_door_state(game, x - 1, y);
	if (map[y][x + 1] == 'D' || map[y][x + 1] == 'd')
		change_door_state(game, x + 1, y);
	if (map[y + 1][x] == 'D' || map[y + 1][x] == 'd')
		change_door_state(game, x, y + 1);
	if (map[y + 1][x - 1] == 'D' || map[y + 1][x - 1] == 'd')
		change_door_state(game, x - 1, y + 1);
	if (map[y + 1][x + 1] == 'D' || map[y + 1][x + 1] == 'd')
		change_door_state(game, x + 1, y + 1);
}

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
	if (keycode == 101)
		open_door(game, (int)game->player->pos_x, (int)game->player->pos_y, game->map);
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
	return (0);
}

/* Rotate player if mouse x-axis has changed */
int	mouse(int x, int y, t_game *game)
{
	int		delta_x;
	double	old_dir_x;
	double	old_plane_x;

	if (game->key->last_x == -1)
	{
		game->key->last_x = x;
		return (0);
	}
	delta_x = x - game->key->last_x;
	game->key->last_x = x;
	old_dir_x = game->player->dir_x;
	game->player->dir_x = game->player->dir_x * cos(-delta_x * ROT_SPEED)
		- game->player->dir_y * sin(-delta_x * ROT_SPEED);
	game->player->dir_y = old_dir_x * sin(-delta_x * ROT_SPEED)
		+ game->player->dir_y * cos(-delta_x * ROT_SPEED);
	old_plane_x = game->player->plane_x;
	game->player->plane_x = game->player->plane_x * cos(-delta_x * ROT_SPEED)
		- game->player->plane_y * sin(-delta_x * ROT_SPEED);
	game->player->plane_y = old_plane_x * sin(-delta_x * ROT_SPEED)
		+ game->player->plane_y * cos(-delta_x * ROT_SPEED);
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
		if (game->map[temp_x][temp_y] != '1' && game->map[temp_x][temp_y] != 'D')
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
		if (game->map[temp_x][temp_y] != '1' && game->map[temp_x][temp_y] != 'D')
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
		if (game->map[temp_x][temp_y] != '1' && game->map[temp_x][temp_y] != 'D')
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
		if (game->map[temp_x][temp_y] != '1' && game->map[temp_x][temp_y] != 'D')
		{
			game->player->pos_x -= game->player->dir_y * speed;
			game->player->pos_y += game->player->dir_x * speed;
		}
	}
}
