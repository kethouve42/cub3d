/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map_bis.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acasanov <acasanov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 16:50:59 by acasanov          #+#    #+#             */
/*   Updated: 2024/07/24 18:57:31 by acasanov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/* Check the validity of a character on the map */
int	is_valid_char(char c)
{
	if (c == '1' || c == '0' || c == 'N' || c == 'S' || c == 'E' || c == 'W'
		|| c == 'D' ||  c == 'B' ||  c == 'P')
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
void	apply_player_rot(t_game *game, int i, double x_value, double y_value)
{
	if (i == 0)
	{
		game->player->dir_x = x_value;
		game->player->dir_y = y_value;
	}
	else
	{
		game->player->plane_x = x_value;
		game->player->plane_y = y_value;
	}
}

/* Set the player values according to its starting rotation */
void	set_player_rot(t_game *game)
{
	if (game->player_start_rot == 1)
	{
		apply_player_rot(game, 0, -1, 0);
		apply_player_rot(game, 1, 0, 0.66);
	}
	else if (game->player_start_rot == 2)
	{
		apply_player_rot(game, 0, 0, 1);
		apply_player_rot(game, 1, 0.66, 0);
	}
	else if (game->player_start_rot == 3)
	{
		apply_player_rot(game, 0, 1, 0);
		apply_player_rot(game, 1, 0, -0.66);
	}
	else if (game->player_start_rot == 4)
	{
		apply_player_rot(game, 0, 0, -1);
		apply_player_rot(game, 1, -0.66, 0);
	}
}
