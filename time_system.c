/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time_system.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acasanov <acasanov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 16:25:22 by acasanov          #+#    #+#             */
/*   Updated: 2024/07/23 16:02:41 by acasanov         ###   ########.fr       */
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
