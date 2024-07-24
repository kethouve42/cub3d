/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphic_info.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acasanov <acasanov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 20:58:52 by acasanov          #+#    #+#             */
/*   Updated: 2024/07/22 19:32:45 by acasanov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/* Load a .xpm texture */
void	load_texture(t_game *game, t_img *texture, char *file_path)
{
	if (texture->img != NULL)
		close_game(game, "Duplicate texture");
	file_path[ft_strlen(file_path) - 1] = '\0';
	texture->img = mlx_xpm_file_to_image(game->mlx, file_path,
			&texture->width, &texture->height);
	if (!texture->img)
	{
		printf("Failed to load texture: %s\n", file_path);
		close_game(game, NULL);
	}
	texture->data = (int *)mlx_get_data_addr(texture->img,
			&texture->bits_per_pixel, &texture->size_l, &texture->endian);
}

/* Update the tester and return the corresponding texture location */
t_img	*set_test_texture(t_game *game, int *check, int check_tmp)
{
	if (check_tmp == 1)
	{
		if (game->graphics->tex_n.index == 0)
			*check += check_tmp;
		game->graphics->tex_n.index++;
		return (&game->graphics->tex_n.tex[game->graphics->tex_n.index - 1]);
	}
	else if (check_tmp == 10)
	{
		if (game->graphics->tex_s.index == 0)
			*check += check_tmp;
		game->graphics->tex_s.index++;
		return (&game->graphics->tex_s.tex[game->graphics->tex_s.index - 1]);
	}
	else if (check_tmp == 100)
	{
		if (game->graphics->tex_w.index == 0)
			*check += check_tmp;
		game->graphics->tex_w.index++;
		return (&game->graphics->tex_w.tex[game->graphics->tex_w.index - 1]);
	}
	else if (check_tmp == 1000)
	{
		if (game->graphics->tex_e.index == 0)
			*check += check_tmp;
		game->graphics->tex_e.index++;
		return (&game->graphics->tex_e.tex[game->graphics->tex_e.index - 1]);
	}
}

/* Searche for corresponding texture identifier (NO, SO, WE, EA) */
int	test_texture(t_game *game, int *check, int i, int j)
{
	char	*path;
	t_img	*texture;

	texture = NULL;
	if (ft_strncmp(game->cubfile[i] + j, "NO", 2) == 0)
		texture = set_test_texture(game, check, 1);
	else if (ft_strncmp(game->cubfile[i] + j, "SO", 2) == 0)
		texture = set_test_texture(game, check, 10);
	else if (ft_strncmp(game->cubfile[i] + j, "WE", 2) == 0)
		texture = set_test_texture(game, check, 100);
	else if (ft_strncmp(game->cubfile[i] + j, "EA", 2) == 0)
		texture = set_test_texture(game, check, 1000);
	if (texture)
	{
		path = game->cubfile[i] + j + 2;
		path = skip_empty(path);
		load_texture(game, texture, path);
		return (1);
	}
	return (0);
}

/* Searche for any graphic identifier (NO, SO, WE, EA, F, C or other) */
int	test_identifier(t_game *game, int *check, int i, int j)
{
	if (test_texture(game, check, i, j) == 1)
		return (1);
	else if (ft_strncmp(game->cubfile[i] + j, "F", 1) == 0)
	{
		parse_color(game, game->cubfile[i] + j + 1, 'F');
		*check += 10000;
		return (1);
	}
	else if (ft_strncmp(game->cubfile[i] + j, "C", 1) == 0)
	{
		parse_color(game, game->cubfile[i] + j + 1, 'C');
		*check += 100000;
		return (1);
	}
	else if (ft_isalnum(game->cubfile[i][j]) == 1)
	{
		printf("error at line %d + %d : '%c' found\n",
			i + 1, j, *(game->cubfile[i] + j));
		close_game(game, NULL);
	}
	return (0);
}

/* Retrieves all the necessary graphic information (textures and colors) */
void	check_graphics(t_game *game)
{
	int		i;
	int		j;
	int		check;

	check_how_many_texture(game);
	i = 0;
	check = 0;
	while (check != 111111 && game->cubfile[i])
	{
		j = 0;
		while (j < ft_strlen(game->cubfile[i]))
		{
			if (test_identifier(game, &check, i, j) == 1)
				break ;
			j++;
		}
		i++;
	}
	if (check != 111111)
		close_game(game, "Missing graphic info");
	game->graphics->tex_n.index = 0;
	game->graphics->tex_s.index = 0;
	game->graphics->tex_e.index = 0;
	game->graphics->tex_w.index = 0;
	game->line_map = i;
}
