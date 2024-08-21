/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_bis_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acasanov <acasanov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 17:28:30 by acasanov          #+#    #+#             */
/*   Updated: 2024/08/21 18:38:07 by acasanov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	change_door_state(t_game *game, int x, int y)
{
	if (game->map[y][x] == 'D')
		game->map[y][x] = 'd';
	else if (game->map[y][x] == 'd')
	{
		if ((int)game->player->pos_x != y || (int)game->player->pos_y != x)
			game->map[y][x] = 'D';
	}
	else
		printf ("Nani ???\n");
}

void	open_door(t_game *game, int y, int x, char **map)
{
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
