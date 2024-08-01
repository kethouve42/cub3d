/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time_system.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kethouve <kethouve@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 16:25:22 by acasanov          #+#    #+#             */
/*   Updated: 2024/08/01 18:41:49 by kethouve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*
Patch note animated update :
- Creation de time_system.c (ici)
- Ajout dans le .h de 2 valeur time dans game, et de la structure texture
- Suppression des anciennes 4 textures t_img partout
- Maj de set_test_texture() dans graphic_info.c
- Ajout de check_how_many_texture() dans graphic_info_bis.c
- Maj de raycast_part_five() dans raycast_bis.c
- Appel de update_all_sprites_index() dans player() dans cub3d.c
- Modification du free_img() en free_texture() dans close.c
*/

/*
Patch note mouse update :
- Suppression de player_rotation() dans player.c et son appel
- Suppression de old_dir_x et plane_x dans player.c
- Ajout d'un ouveau mlx_hook qui call mouse()
- La fonction mouse, qui la rotaton a la place de player_rotation()
*/

void	update_enemies(t_game *game)
{
	game->enemies.sprite->index++;
	//printf("player_index: %d\n", game->enemies.sprite.index);
	if (game->enemies.sprite->index >= game->enemies.sprite->nb)
		game->enemies.sprite->index = 0;
	//printf("player_index: %d| nb: %d\n", game->enemies.sprite->index, game->enemies.sprite->nb);
	//printf("player_x: %f| player_y: %f\n", game->enemies.sprite->x, game->enemies.sprite->y);
}

void update_sprite(t_game *game)
{
	int i = 0;

	while (i < game->graphics->sprite_count)
	{
		game->graphics->sprites[i]->index++;
		if (game->graphics->sprites[i]->index >= game->graphics->sprites[i]->nb)
			game->graphics->sprites[i]->index = 0;
		i++;
	}
}

void	update_sprite_index(t_game *game, t_texture *tex)
{
	tex->index++;
	if (tex->index >= tex->nb)
		tex->index = 0;
}

void	update_all_sprites_index(t_game *game)
{
	if (get_current_time() - game->last_time_update > SPRITE_UPDATE)
	{
		update_sprite_index(game, &game->graphics->tex_n);
		update_sprite_index(game, &game->graphics->tex_s);
		update_sprite_index(game, &game->graphics->tex_e);
		update_sprite_index(game, &game->graphics->tex_w);
		update_enemies(game);
		update_sprite(game);
		game->last_time_update = get_current_time();
	}
}

int	get_current_time(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) == -1)
		write(2, "gettimeofday() error\n", 22);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}
