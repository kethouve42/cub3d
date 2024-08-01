/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphic_info_bis.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kethouve <kethouve@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 20:58:52 by acasanov          #+#    #+#             */
/*   Updated: 2024/08/01 16:56:50 by kethouve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/* Set all sprites images to NULL */
void	set_img_tex(t_texture *tex)
{
	int	i;

	i = 0;
	while (i < tex->nb)
	{
		tex->tex[i].img = NULL;
		i++;
	}
}

/* Check how many sprites exists into the map */
void	check_how_many_sprites(t_game *game)
{
	int	x;
	int	y;
	int	counter;

	counter = 0;
	y = 0;
	while (y < game->map_height)
	{
		x = 0;
		while (game->map[y][x])
		{
			if (game->map[y][x] == 'B' || game->map[y][x] == 'P')
				counter++;
			x++;
		}
		y++;
	}
	game->graphics->sprites = malloc(sizeof(t_sprite *) * (counter));
}

void	check_how_many_texture_loop(t_game *game, int i, int j)
{
	while (j < ft_strlen(game->cubfile[i]))
	{
		if (ft_strncmp(game->cubfile[i] + j, "NO", 2) == 0)
		{
			game->graphics->tex_n.nb++;
			break ;
		}
		else if (ft_strncmp(game->cubfile[i] + j, "SO", 2) == 0)
		{
			game->graphics->tex_s.nb++;
			break ;
		}
		else if (ft_strncmp(game->cubfile[i] + j, "WE", 2) == 0)
		{
			game->graphics->tex_w.nb++;
			break ;
		}
		else if (ft_strncmp(game->cubfile[i] + j, "EA", 2) == 0)
		{
			game->graphics->tex_e.nb++;
			break ;
		}
		j++;
	}
}

/* Check hom many animated sprites exists for one all textures */
void	check_how_many_texture(t_game *game)
{
	int	i;
	int	j;

	i = 0;
	while (game->cubfile[i])
	{
		j = 0;
		check_how_many_texture_loop(game, i, j);
		i++;
	}
	game->graphics->tex_n.tex = malloc(sizeof(t_img)
			* game->graphics->tex_n.nb);
	game->graphics->tex_s.tex = malloc(sizeof(t_img)
			* game->graphics->tex_s.nb);
	game->graphics->tex_e.tex = malloc(sizeof(t_img)
			* game->graphics->tex_e.nb);
	game->graphics->tex_w.tex = malloc(sizeof(t_img)
			* game->graphics->tex_w.nb);
	set_img_tex(&game->graphics->tex_n);
	set_img_tex(&game->graphics->tex_s);
	set_img_tex(&game->graphics->tex_e);
	set_img_tex(&game->graphics->tex_w);
}

/* Update the tester and return the corresponding texture location - part 2 */
t_img	*set_test_texture_two(t_game *game, int *check, int check_tmp)
{
	if (check_tmp == 100)
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
