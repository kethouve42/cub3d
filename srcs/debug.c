/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acasanov <acasanov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 19:50:08 by acasanov          #+#    #+#             */
/*   Updated: 2024/08/19 19:22:12 by acasanov         ###   ########.fr       */
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
	if (game->gamemode == 2)
	{
		printf("\n\n== Key control 2 ==\n    |%d|\n", game->key2->forward);
		printf("|%d| |%d| |%d|", game->key2->left, game->key2->back,
			game->key2->right);
		printf("     |%d||%d|\n", game->key2->rotate_left,
			game->key2->rotate_right);
	}
}

void	display_player_info(t_player *player)
{
	printf("=== Player info ===\n");
	printf("Position : [%f:%f]\n", player->pos_x, player->pos_y);
	printf("Rotation : [%f:%f]\n", player->dir_x,
		player->dir_y);
	printf("Plane    : [%f:%f]\n", player->plane_x,
		player->plane_y);
	printf("Player start rot : %d", player->player_start_rot);
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
