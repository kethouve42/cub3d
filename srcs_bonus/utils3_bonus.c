/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acasanov <acasanov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 13:28:02 by acasanov          #+#    #+#             */
/*   Updated: 2024/08/21 18:39:17 by acasanov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	init_map_line(t_map	*map, t_player	*player, int x1, int y1)
{
	map->x0 = (int)(player->pos_x * 16);
	map->y0 = (int)(player->pos_y * 16);
	map->color = 0xFF0000;
	map->dx = abs(x1 - map->x0);
	map->dy = abs(y1 - map->y0);
	if (map->x0 < x1)
		map->sx = 1;
	else
		map->sx = -1;
	if (map->y0 < y1)
		map->sy = 1;
	else
		map->sy = -1;
	if (map->dx > map->dy)
		map->err = (map->dx / 2);
	else
		map->err = (-(map->dy) / 2);
}

/* Skip all non-alphanumeric characters */
char	*skip_empty(char *str)
{
	while (!ft_isalnum(*str))
		str++;
	return (str);
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

/* Check if a char is one of the char into str */
int	is_into_str(char c, char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == c)
			return (1);
		i++;
	}
	return (0);
}
