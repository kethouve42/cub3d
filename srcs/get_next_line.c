/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acasanov <acasanov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 15:09:37 by acasanov          #+#    #+#             */
/*   Updated: 2023/12/04 16:45:07 by acasanov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_strchr(const char *s, int c)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == (char)c)
			return ((char *)(s + i));
		i++;
	}
	if (s[i] == (char)c)
		return ((char *)(s + i));
	return (NULL);
}

// Lit le fichier fd et remplit la stash jusqu'a \n
// (penser a reset le buffer a chaque passage)
char	*read_and_stash(int fd, char *stash)
{
	char	*buffer;
	int		readed;

	if (!stash)
		return (stash);
	readed = 1;
	buffer = ft_calloc((BUFFER_SIZE + 1), sizeof(char));
	if (buffer == NULL)
		return ("");
	while (!ft_strchr(stash, '\n') && readed != 0)
	{
		readed = read(fd, buffer, BUFFER_SIZE);
		if (readed <= 0)
			break ;
		stash = ft_strjoinfree(stash, buffer);
		ft_bzero(buffer, BUFFER_SIZE + 1);
	}
	free(buffer);
	return (stash);
}

// Recupere et retourne le contenu de la stash jusqu'au \n (si il y a)
char	*get_line_into_stash(char *stash)
{
	int		i;
	char	*line;

	if (*stash == '\0')
		return (NULL);
	i = 0;
	while (stash[i] != '\n' && stash[i])
		i++;
	line = ft_calloc(i + 2, sizeof(char));
	i = 0;
	while (stash[i])
	{
		line[i] = stash[i];
		if (stash[i] == '\n')
			break ;
		i++;
	}
	return (line);
}

// Nettoie la stash de la ligne retournee
char	*clear_stash(char *stash, char *line)
{
	char	*new_stash;
	int		i;

	i = 0;
	new_stash = NULL;
	if (line)
	{
		i = ft_strlen(line);
		new_stash = ft_strdup(stash + i);
	}
	free (stash);
	return (new_stash);
}

char	*get_next_line(int fd)
{
	static char	*stash = NULL;
	char		*line;

	line = NULL;
	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0)
	{
		free(stash);
		stash = NULL;
		return (NULL);
	}
	if (!stash)
		stash = ft_strdup("");
	stash = read_and_stash(fd, stash);
	line = get_line_into_stash(stash);
	if (stash != NULL)
		stash = clear_stash(stash, line);
	return (line);
}

/*#include <fcntl.h>

int	main(void)
{
	int	fd;
	char	*line;
    int	i;

	i = 1;
	fd = open("test", O_RDONLY);
	while (i < 10)
	{
		line = get_next_line(fd);
		if (line == NULL)
		{
			printf("--------\nline %d : null\n--------\n", i);
			free(line);
			break;
		}
		printf("--------\nline %d : %s\n--------\n", i, line);
		free(line);
        i++;
	}
	return (0);
}*/
