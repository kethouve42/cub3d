/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphic_info_bis.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acasanov <acasanov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 20:58:52 by acasanov          #+#    #+#             */
/*   Updated: 2024/07/22 19:31:43 by acasanov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/* Atoi a RGB number and applies it (R = 0, G = 1, B = 2) */
void	get_color_value(t_game *game, char c, char *str, int rgb)
{
	int	color;

	if (ft_isnum(*str))
		color = ft_atoi(str);
	else
		close_game(game, "Syntax color error");
	if (color < 0 || color > 255)
		close_game(game, "Color value error");
	if (c == 'C')
		game->graphics->color_sky[rgb] = ft_atoi(str);
	else
		game->graphics->color_ground[rgb] = ft_atoi(str);
}

/* Get and store RGB values */
void	parse_color(t_game *game, char *str, char c)
{
	str = skip_empty(str);
	get_color_value(game, c, str, 0);
	while (ft_isnum(*str))
		str++;
	if (*str != ',')
		close_game(game, "syntax color error");
	str++;
	str = skip_empty(str);
	get_color_value(game, c, str, 1);
	while (ft_isnum(*str))
		str++;
	if (*str != ',')
		close_game(game, "syntax color error");
	str++;
	str = skip_empty(str);
	get_color_value(game, c, str, 2);
}

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

/* Check hom many animated sprites exists for one all textures */
void	check_how_many_texture(t_game *game) // Trop de lignes, mais de toute facon on risaue de remplacer les NO/SO/EA/WE
{
	int	i;
	int	j;

	game->graphics->tex_n.nb = 0;
	game->graphics->tex_s.nb = 0;
	game->graphics->tex_e.nb = 0;
	game->graphics->tex_w.nb = 0;
	i = 0;
	while (game->cubfile[i])
	{
		j = 0;
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
