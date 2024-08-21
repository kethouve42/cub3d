/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_bis_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kethouve <kethouve@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 16:18:24 by acasanov          #+#    #+#             */
/*   Updated: 2024/08/21 19:13:43 by kethouve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	sprite_init_bis(t_game *game)
{
	game->graphics->tmp_path = ft_strdup("texture/demon3.xpm\n");
	load_texture(game, &game->graphics->s_enemi_dead, game->graphics->tmp_path);
	free(game->graphics->tmp_path);
	game->graphics->tmp_path = NULL;
	game->graphics->tmp_path = ft_strdup("texture/marine_face_1.xpm\n");
	load_texture(game, &game->graphics->s_pl_face1, game->graphics->tmp_path);
	free(game->graphics->tmp_path);
	game->graphics->tmp_path = NULL;
	game->graphics->tmp_path = ft_strdup("texture/marine_face_2.xpm\n");
	load_texture(game, &game->graphics->s_pl_face2, game->graphics->tmp_path);
	free(game->graphics->tmp_path);
	game->graphics->tmp_path = NULL;
	game->graphics->tmp_path = ft_strdup("texture/marine_back_1.xpm\n");
	load_texture(game, &game->graphics->s_pl_back1, game->graphics->tmp_path);
	free(game->graphics->tmp_path);
	game->graphics->tmp_path = NULL;
	game->graphics->tmp_path = ft_strdup("texture/marine_back_2.xpm\n");
	load_texture(game, &game->graphics->s_pl_back2, game->graphics->tmp_path);
	free(game->graphics->tmp_path);
	game->graphics->tmp_path = NULL;
	game->graphics->tmp_path = ft_strdup("texture/marine_left_1.xpm\n");
	load_texture(game, &game->graphics->s_pl_left1, game->graphics->tmp_path);
	free(game->graphics->tmp_path);
	game->graphics->tmp_path = NULL;
}

void	sprite_init(t_game *game)
{
	game->graphics->tmp_path = ft_strdup("texture/pillar.xpm\n");
	load_texture(game, &game->graphics->s_pillar, game->graphics->tmp_path);
	free(game->graphics->tmp_path);
	game->graphics->tmp_path = NULL;
	game->graphics->tmp_path = ft_strdup("texture/barrel.xpm\n");
	load_texture(game, &game->graphics->s_barrel, game->graphics->tmp_path);
	free(game->graphics->tmp_path);
	game->graphics->tmp_path = NULL;
	game->graphics->tmp_path = ft_strdup("texture/newdoor1.xpm\n");
	load_texture(game, &game->graphics->tex_door, game->graphics->tmp_path);
	free(game->graphics->tmp_path);
	game->graphics->tmp_path = NULL;
	game->graphics->tmp_path = ft_strdup("texture/newdoor2.xpm\n");
	load_texture(game, &game->graphics->tex_door2, game->graphics->tmp_path);
	free(game->graphics->tmp_path);
	game->graphics->tmp_path = NULL;
	game->graphics->tmp_path = ft_strdup("texture/demon.xpm\n");
	load_texture(game, &game->graphics->s_enemi_one, game->graphics->tmp_path);
	free(game->graphics->tmp_path);
	game->graphics->tmp_path = NULL;
	game->graphics->tmp_path = ft_strdup("texture/demon2.xpm\n");
	load_texture(game, &game->graphics->s_enemi_two, game->graphics->tmp_path);
	free(game->graphics->tmp_path);
	game->graphics->tmp_path = NULL;
}

void	init_tex_wall(t_game *game)
{
	game->graphics->tex_n.index = 0;
	game->graphics->tex_n.nb = 0;
	game->graphics->tex_n.tex = NULL;
	game->graphics->tex_s.index = 0;
	game->graphics->tex_s.nb = 0;
	game->graphics->tex_s.tex = NULL;
	game->graphics->tex_e.index = 0;
	game->graphics->tex_e.nb = 0;
	game->graphics->tex_e.tex = NULL;
	game->graphics->tex_w.index = 0;
	game->graphics->tex_w.nb = 0;
	game->graphics->tex_w.tex = NULL;
}

void	init_img_sprite(t_game *game)
{
	game->graphics->s_pillar.img = NULL;
	game->graphics->s_barrel.img = NULL;
	game->graphics->tex_door.img = NULL;
	game->graphics->tex_door2.img = NULL;
	game->graphics->s_enemi_one.img = NULL;
	game->graphics->s_enemi_two.img = NULL;
	game->graphics->s_enemi_dead.img = NULL;
	game->graphics->s_pl_back1.img = NULL;
	game->graphics->s_pl_back2.img = NULL;
	game->graphics->s_pl_face1.img = NULL;
	game->graphics->s_pl_face2.img = NULL;
	game->graphics->s_pl_left1.img = NULL;
	game->graphics->s_pl_left2.img = NULL;
	game->graphics->s_pl_right1.img = NULL;
	game->graphics->s_pl_right2.img = NULL;
}

/* Setup the default values ​​of the window */
void	graphic_init(t_game *game)
{
	int	i;

	game->graphics = malloc(sizeof(t_graphics));
	game->graphics->sprites = NULL;
	game->graphics->screen_lenght = 24 * 64;
	if (game->gamemode == 2)
		game->graphics->screen_lenght += 24 * 64 + 10;
	game->graphics->screen_height = 13 * 64;
	init_tex_wall(game);
	init_img_sprite(game);
	game->graphics->sprite_count = 0;
	i = 0;
	game->z_buffer = (double *)malloc(sizeof(double)
			* (game->graphics->screen_lenght));
	while (i < game->graphics->screen_lenght)
	{
		game->z_buffer[i] = 0;
		i++;
	}
}
