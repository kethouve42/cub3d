/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map_bis.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acasanov <acasanov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 16:50:59 by acasanov          #+#    #+#             */
/*   Updated: 2024/08/19 19:11:18 by acasanov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/* Check the validity of a character on the map */
int	is_valid_char(char c)
{
	if (c == '1' || c == '0' || c == 'N' || c == 'S' || c == 'E' || c == 'W'
		|| c == 'D' || c == 'B' || c == 'P' || c == 'G')
		return (1);
	return (0);
}

/* Check the validity of the surrounding 8 characters */
int	is_valid_coord(t_game *game, char **map, int x, int y)
{
	if (y == 0 || !map[y - 1][x] || is_valid_char(map[y - 1][x]) == 0)
		return (printf("Error\nInvalid map at %d:%d\n", x + 1, y + 1), 1);
	if (!map[y - 1][x - 1] || is_valid_char(map[y - 1][x - 1]) == 0)
		return (printf("Error\nInvalid map at %d:%d\n", x + 1, y + 1), 1);
	if (!map[y - 1][x + 1] || is_valid_char(map[y - 1][x + 1]) == 0)
		return (printf("Error\nInvalid map at %d:%d\n", x + 1, y + 1), 1);
	if (x == 0 || !map[y][x - 1] || is_valid_char(map[y][x - 1]) == 0)
		return (printf("Error\nInvalid map at %d:%d\n", x + 1, y + 1), 1);
	if (x == ft_strlen(map[y]) || !map[y][x + 1]
		|| is_valid_char(map[y][x + 1]) == 0)
		return (printf("Error\nInvalid map at %d:%d\n", x + 1, y + 1), 1);
	if (y == game->map_height || !map[y + 1][x]
		|| is_valid_char(map[y + 1][x]) == 0)
		return (printf("Error\nInvalid map at %d:%d\n", x + 1, y + 1), 1);
	if (!map[y + 1][x - 1] || is_valid_char(map[y + 1][x - 1]) == 0)
		return (printf("Error\nInvalid map at %d:%d\n", x + 1, y + 1), 1);
	if (!map[y + 1][x + 1] || is_valid_char(map[y + 1][x + 1]) == 0)
		return (printf("Error\nInvalid map at %d:%d\n", x + 1, y + 1), 1);
	return (0);
}

/* Apply x and y values ​​to player direction or plane */
void	apply_player_rot(t_player *player, int i, double xvalue, double yvalue)
{
	if (i == 0)
	{
		player->dir_x = xvalue;
		player->dir_y = yvalue;
	}
	else
	{
		player->plane_x = xvalue;
		player->plane_y = yvalue;
	}
}

/* Set the player values according to its starting rotation */
void	set_player_rot(t_player *player)
{
	if (player->player_start_rot == 1)
	{
		apply_player_rot(player, 0, -1, 0);
		apply_player_rot(player, 1, 0, 0.66);
	}
	else if (player->player_start_rot == 2)
	{
		apply_player_rot(player, 0, 0, 1);
		apply_player_rot(player, 1, 0.66, 0);
	}
	else if (player->player_start_rot == 3)
	{
		apply_player_rot(player, 0, 1, 0);
		apply_player_rot(player, 1, 0, -0.66);
	}
	else if (player->player_start_rot == 4)
	{
		apply_player_rot(player, 0, 0, -1);
		apply_player_rot(player, 1, -0.66, 0);
	}
}
