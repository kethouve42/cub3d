/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphic_info_ter.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acasanov <acasanov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 16:44:19 by acasanov          #+#    #+#             */
/*   Updated: 2024/08/12 16:16:07 by acasanov         ###   ########.fr       */
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
