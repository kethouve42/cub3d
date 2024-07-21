/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acasanov <acasanov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 19:50:08 by acasanov          #+#    #+#             */
/*   Updated: 2024/07/21 20:35:09 by acasanov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* ================================ DEBUG =================================== */
/* =============== Here are some pre-made debugging functions =============== */
/* = Call them wherever you want as part of the code (especially in player) = */
/* ========================================================================== */

#include "cub3d.h"

void	display_map(char **map)
{
	int	i;

	i = 0;
	printf("=== Map ===\n");
	while (map[i])
	{
		printf("%s", map[i]);
		i++;
	}
	printf("\n");
}

void	display_key_input(t_game *game)
{
	printf("\n== Key control ==\n    |%d|\n", game->key->forward);
	printf("|%d| |%d| |%d|", game->key->left, game->key->back,
		game->key->right);
	printf("     |%d||%d|\n", game->key->rotate_left,
		game->key->rotate_right);
}

void	display_player_info(t_game *game)
{
	printf("=== Player info ===\nPosition : [%f:%f]\n",
		game->player->pos_x, game->player->pos_y);
	printf("Rotation : [%f:%f]\n", game->player->dir_x,
		game->player->dir_y);
	printf("Plane    : [%f:%f]\n", game->player->plane_x,
		game->player->plane_y);
	printf("\n");
}

void	display_texture_info(t_img *texture)
{
	printf("=== Texture info ===\n");
	printf("Size : %dx%d\n", texture->width, texture->height);
	printf("addr: %s\ndata : %d\nsize_l : %d\n", texture->addr,
		*texture->data, texture->size_l);
	printf("bit per pixel : %dd\nline lenght : %d\nendian : %d\n",
		texture->bits_per_pixel, texture->line_length, texture->endian);
	printf("\n");
}

void	display_color(t_game *game)
{
	printf("=== Color background ===\n");
	printf("Sky color    : %d,%d,%d\n", game->graphics->color_sky[0],
		game->graphics->color_sky[1], game->graphics->color_sky[2]);
	printf("Ground color : %d,%d,%d\n",
		game->graphics->color_ground[0], game->graphics->color_ground[1],
		game->graphics->color_ground[2]);
	printf("\n");
}
