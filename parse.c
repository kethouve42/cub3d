/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acasanov <acasanov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 15:56:15 by acasanov          #+#    #+#             */
/*   Updated: 2024/07/18 19:44:29 by acasanov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/* Compte le nombre de lignes d'un fichier */
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

/* Retoure une copie du fichier indique, en sautat les 'overrides' premieres lignes */
char **copy_map(char *map_path, t_game *game, int file_size, int override)
{
	char	**map;
	int		fd;
	int		i;

	fd = open(map_path, O_RDONLY);
	if (fd == -1)
		return NULL;
	map = ft_calloc(sizeof(char *), file_size + 1);
	i = 0;
    char *buff;

    while(override > 0)
    {
        buff = get_next_line(fd);
        free(buff);
        override--;
    }

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
    if (texture->img != NULL)
        close_game(game, "Doublon de texture");
    file_path[ft_strlen(file_path) - 1] = '\0';
    texture->img = mlx_xpm_file_to_image(game->mlx, file_path, &texture->width, &texture->height);
    if (!texture->img)
    {
        printf("Failed to load texture: %s\n", file_path);
        close_game(game, NULL);   
    }
	//printf("load texture w: %d h:%d\n", texture->width, texture->height);
    texture->data = (int *)mlx_get_data_addr(texture->img, &texture->bits_per_pixel, &texture->size_l, &texture->endian);
}

/* C'est moche, mais ca marche ! */
void    parse_color(t_game *game, char *str, char c)
{
    while(*str == ' ')
        str++;
    if(ft_isnum(*str))
    {
        if (c == 'C')
        {
            game->graphics->color_sky[0] = ft_atoi(str);
            if (game->graphics->color_sky[0] < 0 || game->graphics->color_sky[0] > 255)
                close_game(game, "color value error");
        }
        else
        {
            game->graphics->color_ground[0] = ft_atoi(str);
            if (game->graphics->color_ground[0] < 0 || game->graphics->color_ground[0] > 255)
                close_game(game, "color value error");
        }
    }
    else
        close_game(game, "syntax color error");
    while(ft_isnum(*str))
        str++;
    if(*str != ',')
        close_game(game, "syntax color error");
    str++;
    if(ft_isnum(*str))
    {
        if (c == 'C')
        {
            game->graphics->color_sky[1] = ft_atoi(str);
            if (game->graphics->color_sky[1] < 0 || game->graphics->color_sky[1] > 255)
                close_game(game, "color value error");
        }
        else
        {
            game->graphics->color_ground[1] = ft_atoi(str);
            if (game->graphics->color_ground[1] < 0 || game->graphics->color_ground[1] > 255)
                close_game(game, "color value error");
        }
    }
    else
        close_game(game, "syntax color error");
    while(ft_isnum(*str))
        str++;
    if(*str != ',')
        close_game(game, "syntax color error");
    str++;
    if(ft_isnum(*str))
    {
        if (c == 'C')
        {
            game->graphics->color_sky[2] = ft_atoi(str);
            if (game->graphics->color_sky[2] < 0 || game->graphics->color_sky[2] > 255)
                close_game(game, "color value error");
        }
        else
        {
            game->graphics->color_ground[2] = ft_atoi(str);
            if (game->graphics->color_ground[2] < 0 || game->graphics->color_ground[2] > 255)
                close_game(game, "color value error");
        }
    }
    else
        close_game(game, "syntax color error");
    //if(c == 'C')
        //printf("Sky color : %d,%d,%d\n", game->graphics->color_sky[0], game->graphics->color_sky[1], game->graphics->color_sky[2]);
    //else
        //printf("Ground color : %d,%d,%d\n", game->graphics->color_ground[0], game->graphics->color_ground[1], game->graphics->color_ground[2]);
}

void check_texture(t_game *game)
{
    int i = 0;
    int j = 0;
    char *path;
    int check = 0;

    while(check != 111111 && game->cubfile[i])
    {
        j = 0;
        while(j < ft_strlen(game->cubfile[i]))
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
            else if(ft_isalnum(game->cubfile[i][j]) == 1)
            {
                printf("error at line %d + %d : '%c' found\n", i+1, j, *(game->cubfile[i] + j));
                close_game(game, NULL);
            }
            j++;
        }
        i++;
    }
    if (check != 111111)
        close_game(game, "Missing graphic info");
    game->lineMap = i;
}

int is_valid_map(char c)
{
    if(c == '1' || c == '0' || c == 'N' || c == 'S' || c == 'E' || c == 'W')
        return (1);
    return (0);
}

int is_valid_coord(t_game *game, char **map, int x, int y)
{
    //printf("test %d:%d -> %c\n", x+1, y+1, map[y - 1][x]);

    // au dessus
    if(y == 0 || !map[y - 1][x] || is_valid_map(map[y - 1][x]) == 0) 
        return (printf("Error\nInvalid map at %d:%d\n", x + 1, y + 1), 1);
    // au dessus gauche
    if(!map[y - 1][x - 1] || is_valid_map(map[y - 1][x - 1]) == 0)
        return (printf("Error\nInvalid map at %d:%d\n", x + 1, y + 1), 1);
    // au dessus droite
    if(!map[y - 1][x + 1] || is_valid_map(map[y - 1][x + 1]) == 0)
        return (printf("Error\nInvalid map at %d:%d\n", x + 1, y + 1), 1);
    // a gauche
    if(x == 0 || !map[y][x - 1] || is_valid_map(map[y][x - 1]) == 0) 
        return (printf("Error\nInvalid map at %d:%d\n", x + 1, y + 1), 1);
    // a droite
    if(x == ft_strlen(map[y]) || !map[y][x + 1] || is_valid_map(map[y][x + 1]) == 0) 
        return (printf("Error\nInvalid map at %d:%d\n", x + 1, y + 1), 1);
    // en dessous
    if(y == game->mapHeight || !map[y + 1][x] || is_valid_map(map[y + 1][x]) == 0) 
        return (printf("Error\nInvalid map at %d:%d\n", x + 1, y + 1), 1);
    // en dessous gauche
    if(!map[y + 1][x - 1] || is_valid_map(map[y + 1][x - 1]) == 0)
        return (printf("Error\nInvalid map at %d:%d\n", x + 1, y + 1), 1);
    // en dessous droite
    if(!map[y + 1][x + 1] || is_valid_map(map[y + 1][x + 1]) == 0)
        return (printf("Error\nInvalid map at %d:%d\n", x + 1, y + 1), 1);
    return (0);
}

void set_player_rot(t_game *game)
{
    if (game->playerStartRot == 1) // Nord
    {
        game->player->dirX = -1;
	    game->player->dirY = 0;
	    game->player->planeX = 0;
	    game->player->planeY = 0.66;
    }
    else if(game->playerStartRot == 2) // Est
    {
        game->player->dirX = 0;
	    game->player->dirY = 1;
	    game->player->planeX = 0.66;
	    game->player->planeY = 0;
    }
    else if(game->playerStartRot == 3) // Sud
    {
        game->player->dirX = 1;
	    game->player->dirY = 0;
	    game->player->planeX = 0;
	    game->player->planeY = -0.66;
    }
    else if(game->playerStartRot == 4) // Ouest
    {
        game->player->dirX = 0;
	    game->player->dirY = -1;
	    game->player->planeX = -0.66;
	    game->player->planeY = 0;
    }
}

void check_map(t_game *game, char *map_path, int file_size)
{
    char **map;

    while(ft_line_empty(game->cubfile[game->lineMap]) == 0)
        game->lineMap++;

    map = copy_map(map_path, game, file_size - game->lineMap, game->lineMap);
    
    //calcul de length et height
    int y = 0;
    game->mapHeight = file_size - game->lineMap;
    while (y < game->mapHeight)
    {
        if(ft_strlen(map[y]) - 1 > game->mapLength)
        {
            if(y == game->mapHeight)
                game->mapLength = ft_strlen(map[y]);
            else
                game->mapLength = ft_strlen(map[y]) - 1;
        }
        y++;
    }

    // check si ligne vide en plein milieu de map
    y = 0;
    int check = 1;
    while(y < game->mapHeight)
    {
        if(ft_line_empty(map[y]) == 1)
        {
            if (check == 0)
                close_game(game, "Empty line in map");
            check = 1;
        }
        else
            check = 0;
        y++;
    }

    int x = 0;
    y = 0;

    while(y < game->mapHeight)
    {
        x = 0;
        while(map[y][x])
        {
            if(is_valid_map(map[y][x]) == 1 || map[y][x] == ' ' || map[y][x] == '\n')
            {
                if(map[y][x] == '0' || map[y][x] == 'N' || map[y][x] == 'S' || map[y][x] == 'E' || map[y][x] == 'W')
                {
                    if(is_valid_coord(game, map, x, y) == 1)
                        close_game(game, NULL);
                    else
                    {
                        if (map[y][x] != '0')
                        {
                            //printf("Player : %c into [%d:%d]\n", map[y][x], x + 1, y + 1);
                            if(game->playerStartRot != 0)
                                close_game(game, "Two or more player found");
                            game->player->posX = y;
                            game->player->posY = x;
                            if (map[y][x] == 'N')
                                game->playerStartRot = 1;
                            else if (map[y][x] == 'E')
                                game->playerStartRot = 2;
                            else if (map[y][x] == 'S')
                                game->playerStartRot = 3;
                            else if (map[y][x] == 'W')
                                game->playerStartRot = 4;
                            map[y][x] = '0';
                        }
                    }
                }
            }
            else
            {
                printf("error: wrong char at %d:%d (%c found)\n", x, y, map[y][x]);
                close_game(game, NULL);
            }
            x++;
        }
        y++;
    }
    set_player_rot(game);

    if(game->playerStartRot == 0)
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
	while (y < game->mapHeight)
	{
		x = 0;
		while (x < ft_strlen(test_map[y]))
		{
			if (test_map[y][x] != '1' && test_map[y][x] != ' ' && test_map[y][x] != '\n')
			{
				printf("error: Une zone de la map n'est pas accessible '%c' at [%d:%d]\n", test_map[y][x], x+1, y+1);
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

	test_map = copy_map(map_path, game, file_size - game->lineMap, game->lineMap);

	pathfinding(test_map, (int)game->player->posY, (int)game->player->posX);
	check_all_one(game, test_map);
	free_tab(test_map);
}

void	map_analysis(t_game *game, char *map_path)
{
    int file_size;

    int i = ft_strlen(map_path) - 1;
    if (map_path[i] != 'b' || map_path[i-1] != 'u' || map_path[i-2] != 'c' || map_path[i-3] != '.')
        close_game(game, "nedd a .cub file");

    file_size = get_lines(game, map_path);
    game->cubfile = copy_map(map_path, game, file_size, 0);

    check_texture(game);
    check_map(game, map_path, file_size);
    check_path(game, map_path, file_size);
}