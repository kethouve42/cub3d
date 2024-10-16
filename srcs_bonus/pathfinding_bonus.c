/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pathfinding_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acasanov <acasanov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 16:41:33 by acasanov          #+#    #+#             */
/*   Updated: 2024/08/21 18:38:03 by acasanov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

/* Explore possible paths and change them to 1 */
void	pathfinding(char **map, int x, int y)
{
	map[y][x] = '1';
	if (is_into_str(map[y + 1][x], "0DGNSEW"))
		pathfinding(map, x, y + 1);
	if (is_into_str(map[y][x + 1], "0DGNSEW"))
		pathfinding(map, x + 1, y);
	if (is_into_str(map[y][x - 1], "0DGNSEW"))
		pathfinding(map, x - 1, y);
	if (is_into_str(map[y - 1][x], "0DGNSEW"))
		pathfinding(map, x, y - 1);
}

/* Checks if the entire map has been validated by pathfinding */
void	check_all_one(t_game *game, char **test_map)
{
	int	y;
	int	x;

	y = 0;
	while (y < game->map_height)
	{
		x = 0;
		while (x < ft_strlen(test_map[y]))
		{
			if (test_map[y][x] != '1' && test_map[y][x]
				!= ' ' && test_map[y][x] != '\n' && test_map[y][x] != 'B'
				&& test_map[y][x] != 'P')
			{
				printf("Error:\n'%c' at [%d:%d] n'est pas accessible\n",
					test_map[y][x], x + 1, y + 1);
				close_game(game, NULL);
			}
			x++;
		}
		y++;
	}
}

/* Check if the entire map could be fully explored */
void	check_path(t_game *game, char *map_path, int file_size)
{
	char	**test_map;
	int		y;
	int		x;

	test_map = copy_map(map_path, game, file_size
			- game->line_map, game->line_map);
	pathfinding(test_map, (int)game->player->pos_y, (int)game->player->pos_x);
	check_all_one(game, test_map);
	free_tab(test_map);
}
