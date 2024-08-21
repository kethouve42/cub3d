/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_bis.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acasanov <acasanov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 16:18:24 by acasanov          #+#    #+#             */
/*   Updated: 2024/08/21 16:20:35 by acasanov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	sprite_init_bis(t_game *game)
{
	game->graphics->tmp_path = ft_strdup("texture/w_guard4.xpm\n");
	load_texture(game, &game->graphics->s_enemi_dead, game->graphics->tmp_path);
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
	game->graphics->tmp_path = ft_strdup("texture/door1.xpm\n");
	load_texture(game, &game->graphics->tex_door, game->graphics->tmp_path);
	free(game->graphics->tmp_path);
	game->graphics->tmp_path = NULL;
	game->graphics->tmp_path = ft_strdup("texture/door3.xpm\n");
	load_texture(game, &game->graphics->tex_door2, game->graphics->tmp_path);
	free(game->graphics->tmp_path);
	game->graphics->tmp_path = NULL;
	game->graphics->tmp_path = ft_strdup("texture/w_guard3.xpm\n");
	load_texture(game, &game->graphics->s_enemi_one, game->graphics->tmp_path);
	free(game->graphics->tmp_path);
	game->graphics->tmp_path = NULL;
	game->graphics->tmp_path = ft_strdup("texture/w_guard2.xpm\n");
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
