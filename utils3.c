/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acasanov <acasanov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 13:28:02 by acasanov          #+#    #+#             */
/*   Updated: 2024/07/25 16:56:12 by acasanov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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
