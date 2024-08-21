/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_ter_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kethouve <kethouve@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 19:04:26 by kethouve          #+#    #+#             */
/*   Updated: 2024/08/21 19:13:50 by kethouve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	sprite_init_ter(t_game *game)
{
	game->graphics->tmp_path = ft_strdup("texture/marine_left_2.xpm\n");
	load_texture(game, &game->graphics->s_pl_left2, game->graphics->tmp_path);
	free(game->graphics->tmp_path);
	game->graphics->tmp_path = NULL;
	game->graphics->tmp_path = ft_strdup("texture/marine_right_1.xpm\n");
	load_texture(game, &game->graphics->s_pl_right1, game->graphics->tmp_path);
	free(game->graphics->tmp_path);
	game->graphics->tmp_path = NULL;
	game->graphics->tmp_path = ft_strdup("texture/marine_right_2.xpm\n");
	load_texture(game, &game->graphics->s_pl_right2, game->graphics->tmp_path);
	free(game->graphics->tmp_path);
	game->graphics->tmp_path = NULL;
}