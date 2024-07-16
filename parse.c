/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acasanov <acasanov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 15:56:15 by acasanov          #+#    #+#             */
/*   Updated: 2024/07/16 18:53:37 by acasanov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/* Compte le nombre de lignes d'un fichier */
int	get_lines(char *map_path)
{
	int		fd;
	int		i;
	char	*line;

	fd = open(map_path, O_RDONLY);
	if (fd == -1)
	{
		printf("Error\nFichier .cub non trouvé\n");
		return (-1);
	}
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

char **copy_map(char *map_path, t_game *game, int file_size)
{
	char	**map;
	int		fd;
	int		i;

	fd = open(map_path, O_RDONLY);
	if (fd == -1)
		return NULL;
	map = malloc(sizeof(char *) * file_size);
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

void    load_texture(t_game *game, t_img *texture, char *file_path)
{
    file_path[ft_strlen(file_path) - 1] = '\0';
    printf("%s\n", file_path);
    texture->img = mlx_xpm_file_to_image(game->mlx, file_path, &texture->width, &texture->height);
    if (!texture->img)
    {
        fprintf(stderr, "Failed to load texture: %s\n", file_path);
        exit(EXIT_FAILURE);
    }
	//printf("load texture w: %d h:%d\n", texture->width, texture->height);
    texture->data = (int *)mlx_get_data_addr(texture->img, &texture->bits_per_pixel, &texture->size_l, &texture->endian);
}

/* C'est moche, mais ca marche ! */
//! et faudra check si entre 0 et 255
int    parse_color(t_game *game, char *str, char c)
{
    while(*str == ' ')
        str++;
    if(ft_isnum(*str))
    {
        if (c == 'C')
            game->graphics->color_sky[0] = ft_atoi(str);
        else
            game->graphics->color_ground[0] = ft_atoi(str);
    }
    else
        return (printf("sytax color error\n"));
    while(ft_isnum(*str))
        str++;
    if(*str != ',')
        return (printf("sytax color error\n"));
    str++;
    if(ft_isnum(*str))
    {
        if (c == 'C')
            game->graphics->color_sky[1] = ft_atoi(str);
        else
            game->graphics->color_ground[1] = ft_atoi(str);
    }
    else
        return (printf("sytax color error\n"));
    while(ft_isnum(*str))
        str++;
    if(*str != ',')
        return (printf("sytax color error\n"));
    str++;
    if(ft_isnum(*str))
    {
        if (c == 'C')
            game->graphics->color_sky[2] = ft_atoi(str);
        else
            game->graphics->color_ground[2] = ft_atoi(str);
    }
    else
        return (printf("sytax color error\n"));

    if(c == 'C')
        printf("Sky color : %d,%d,%d\n", game->graphics->color_sky[0], game->graphics->color_sky[1], game->graphics->color_sky[2]);
    else
        printf("Ground color : %d,%d,%d\n", game->graphics->color_ground[0], game->graphics->color_ground[1], game->graphics->color_ground[2]);
    return 0;
}

int check_texture(t_game *game)
{
    int i = 0;
    int j = 0;
    char *path;
    int check = 0;

    while(game->cubfile[i])
    {
        j = 0;
        while(game->cubfile[j])
        {
            if(ft_strncmp(game->cubfile[i] + j, "NO", 2) == 0)
            {
                path = game->cubfile[i] + j + 2;
                while (*path == ' ')
                    path++;
                load_texture(game, &game->graphics->textN, path);
                check += 1;
                break;
            }
            else if(ft_strncmp(game->cubfile[i] + j, "SO", 2) == 0)
            {
                path = game->cubfile[i] + j + 2;
                while (*path == ' ')
                    path++;
                load_texture(game, &game->graphics->textS, path);
                check += 10;
                break;
            }
            else if(ft_strncmp(game->cubfile[i] + j, "WE", 2) == 0)
            {
                path = game->cubfile[i] + j + 2;
                while (*path == ' ')
                    path++;
                load_texture(game, &game->graphics->textW, path);
                check += 100;
                break;
            }
            else if(ft_strncmp(game->cubfile[i] + j, "EA", 2) == 0)
            {
                path = game->cubfile[i] + j + 2;
                while (*path == ' ')
                    path++;
                load_texture(game, &game->graphics->textE, path);
                check += 1000;
                break;
            }
            else if(ft_strncmp(game->cubfile[i] + j, "F", 1) == 0)
            {
                parse_color(game, game->cubfile[i] + j + 1, 'F');
                check += 10000;
                break;
            }
            else if(ft_strncmp(game->cubfile[i] + j, "C", 1) == 0)
            {
                parse_color(game, game->cubfile[i] + j + 1, 'C');
                check += 100000;
                break;
            }
            j++;
        }
        i++;
    }
    if (check != 111111)
        return(printf("error: missing graphic info\n"), 1);
    return (0);
}


int	map_analysis(t_game *game, char *map_path)
{
	int	check;
    int file_size;

    file_size = get_lines(map_path);
    game->cubfile = copy_map(map_path, game, file_size);

    //display_map(game->cubfile);

	check = 0;
    check += check_texture(game);

	/*check += check_caracters(game);
	check += check_size(game);
	check += check_walls(game);
	if (check == 0)
		check += check_path(game);*/
	if (check > 0)
	{
		printf("Contenu de la map incorrect\n");
		return (1);
	}
	return (0);
}