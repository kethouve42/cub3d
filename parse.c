/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acasanov <acasanov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 15:56:15 by acasanov          #+#    #+#             */
/*   Updated: 2024/07/20 21:44:19 by acasanov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/* Count the number of lines in a file */
int	get_lines(t_game *game, char *map_path)
{
	int		fd;
	int		i;
	char	*line;

	fd = open(map_path, O_RDONLY);
	if (fd == -1)
		close_game(game, "Fichier .cub non trouvé");
	i = 0;
	line = get_next_line(fd);
	while (line != NULL)
	{
		i++;
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	return (i);
}

/* Returns a copy of the file, skipping the first lines 'overrides' */
char	**copy_map(char *map_path, t_game *game, int file_size, int override)
{
	char	**map;
	char	*buff;
	int		fd;
	int		i;

	fd = open(map_path, O_RDONLY);
	if (fd == -1)
		close_game(game, "Impossible d'ouvrir le fichier");
	map = ft_calloc(sizeof(char *), file_size + 1);
	while (override > 0)
	{
		buff = get_next_line(fd);
		free(buff);
		override--;
	}
	i = 0;
	while (i < file_size)
	{
		map[i] = get_next_line(fd);
		i++;
	}
	map[i] = '\0';
	get_next_line(fd);
	close(fd);
	return (map);
}

int	is_valid_map(char c)
{
	if (c == '1' || c == '0' || c == 'N' || c == 'S' || c == 'E' || c == 'W')
		return (1);
	return (0);
}

int	is_valid_coord(t_game *game, char **map, int x, int y)
{
	//printf("test %d:%d -> %c\n", x+1, y+1, map[y - 1][x]);
	// au dessus
	if (y == 0 || !map[y - 1][x] || is_valid_map(map[y - 1][x]) == 0)
		return (printf("Error\nInvalid map at %d:%d\n", x + 1, y + 1), 1);
	// au dessus gauche
	if (!map[y - 1][x - 1] || is_valid_map(map[y - 1][x - 1]) == 0)
		return (printf("Error\nInvalid map at %d:%d\n", x + 1, y + 1), 1);
	// au dessus droite
	if (!map[y - 1][x + 1] || is_valid_map(map[y - 1][x + 1]) == 0)
		return (printf("Error\nInvalid map at %d:%d\n", x + 1, y + 1), 1);
	// a gauche
	if (x == 0 || !map[y][x - 1] || is_valid_map(map[y][x - 1]) == 0)
		return (printf("Error\nInvalid map at %d:%d\n", x + 1, y + 1), 1);
	// a droite
	if (x == ft_strlen(map[y]) || !map[y][x + 1]
		|| is_valid_map(map[y][x + 1]) == 0)
		return (printf("Error\nInvalid map at %d:%d\n", x + 1, y + 1), 1);
	// en dessous
	if (y == game->map_height || !map[y + 1][x]
		|| is_valid_map(map[y + 1][x]) == 0)
		return (printf("Error\nInvalid map at %d:%d\n", x + 1, y + 1), 1);
	// en dessous gauche
	if (!map[y + 1][x - 1] || is_valid_map(map[y + 1][x - 1]) == 0)
		return (printf("Error\nInvalid map at %d:%d\n", x + 1, y + 1), 1);
	// en dessous droite
	if (!map[y + 1][x + 1] || is_valid_map(map[y + 1][x + 1]) == 0)
		return (printf("Error\nInvalid map at %d:%d\n", x + 1, y + 1), 1);
	return (0);
}

void	set_player_rot(t_game *game)
{
	if (game->player_start_rot == 1) // Nord
	{
		game->player->dir_x = -1;
		game->player->dir_y = 0;
		game->player->plane_x = 0;
		game->player->plane_y = 0.66;
	}
	else if (game->player_start_rot == 2) // Est
	{
		game->player->dir_x = 0;
		game->player->dir_y = 1;
		game->player->plane_x = 0.66;
		game->player->plane_y = 0;
	}
	else if (game->player_start_rot == 3) // Sud
	{
		game->player->dir_x = 1;
		game->player->dir_y = 0;
		game->player->plane_x = 0;
		game->player->plane_y = -0.66;
	}
	else if (game->player_start_rot == 4) // Ouest
	{
		game->player->dir_x = 0;
		game->player->dir_y = -1;
		game->player->plane_x = -0.66;
		game->player->plane_y = 0;
	}
}

void	check_map(t_game *game, char *map_path, int file_size)
{
	char	**map;
	int		check;
	int		y;
	int		x;

	while (game->cubfile[game->line_map]
		&& ft_line_empty(game->cubfile[game->line_map]) == 0)
		game->line_map++;
	if (game->cubfile[game->line_map] == NULL)
		close_game(game, "No maps found");
	map = copy_map(map_path, game, file_size - game->line_map, game->line_map);
	//calcul de length et height
	game->map_height = file_size - game->line_map;
	y = 0;
	while (y < game->map_height)
	{
		if (ft_strlen(map[y]) - 1 > game->map_length)
		{
			if (y == game->map_height)
				game->map_length = ft_strlen(map[y]);
			else
				game->map_length = ft_strlen(map[y]) - 1;
		}
		y++;
	}
	// check si ligne vide en plein milieu de map
	y = 0;
	check = 1;
	while (y < game->map_height)
	{
		if (ft_line_empty(map[y]) == 1)
		{
			if (check == 0)
				close_game(game, "Empty line in map");
			check = 1;
		}
		else
			check = 0;
		y++;
	}
	y = 0;
	while (y < game->map_height)
	{
		x = 0;
		while (map[y][x])
		{
			if (is_valid_map(map[y][x]) == 1 || map[y][x] == ' '
				|| map[y][x] == '\n')
			{
				if (map[y][x] == '0' || map[y][x] == 'N' || map[y][x] == 'S'
					|| map[y][x] == 'E' || map[y][x] == 'W')
				{
					if (is_valid_coord(game, map, x, y) == 1)
						close_game(game, NULL);
					else
					{
						if (map[y][x] != '0')
						{
							//printf("Player : %c into [%d:%d]\n"
							//	, map[y][x], x + 1, y + 1);
							if (game->player_start_rot != 0)
								close_game(game, "Two or more player found");
							game->player->pos_x = y;
							game->player->pos_y = x;
							if (map[y][x] == 'N')
								game->player_start_rot = 1;
							else if (map[y][x] == 'E')
								game->player_start_rot = 2;
							else if (map[y][x] == 'S')
								game->player_start_rot = 3;
							else if (map[y][x] == 'W')
								game->player_start_rot = 4;
							map[y][x] = '0';
						}
					}
				}
			}
			else
			{
				printf("error: wrong char at %d:%d (%c found)\n",
					x, y, map[y][x]);
				close_game(game, NULL);
			}
			x++;
		}
		y++;
	}
	set_player_rot(game);
	if (game->player_start_rot == 0)
		close_game(game, "error : no player found");
	game->map = map;
}

void	pathfinding(char **map, int x, int y)
{
	map[y][x] = '1';
	if (map[y + 1][x] == '0')
		pathfinding(map, x, y + 1);
	if (map[y][x + 1] == '0')
		pathfinding(map, x + 1, y);
	if (map[y][x - 1] == '0')
		pathfinding(map, x - 1, y);
	if (map[y - 1][x] == '0')
		pathfinding(map, x, y - 1);
}

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
				!= ' ' && test_map[y][x] != '\n')
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

void	map_analysis(t_game *game, char *map_path)
{
	int	file_size;
	int	i;

	i = ft_strlen(map_path) - 1;
	if (map_path[i] != 'b' || map_path[i - 1] != 'u'
		|| map_path[i - 2] != 'c' || map_path[i - 3] != '.')
		close_game(game, "need a .cub file");
	file_size = get_lines(game, map_path);
	game->cubfile = copy_map(map_path, game, file_size, 0);
	check_graphics(game);
	check_map(game, map_path, file_size);
	check_path(game, map_path, file_size);
}
