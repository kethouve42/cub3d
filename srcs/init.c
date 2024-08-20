/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acasanov <acasanov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 18:47:52 by acasanov          #+#    #+#             */
/*   Updated: 2024/08/20 19:51:09 by acasanov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_player(t_player *player)
{
	int	i;

	i = 0;
	player->pos_x = 1;
	player->pos_y = 1;
	player->dir_x = -1;
	player->dir_y = 0;
	player->plane_x = 0;
	player->plane_y = 0.66;
	player->player_start_rot = 0;
	player->hp = 5;
	player->sprite = malloc(sizeof(t_sprite));
	player->sprite->s_tex = malloc(sizeof(t_img) * 8);
	while (i < 8)
	{
		player->sprite->s_tex[i].img = NULL;
		i++;
	}
	player->sprite->index = 0;
	player->sprite->nb = 8;
}

void	key_init(t_game *game)
{
	game->key = malloc(sizeof(t_key));
	game->key->forward = 0;
	game->key->back = 0;
	game->key->left = 0;
	game->key->right = 0;
	game->key->rotate_left = 0;
	game->key->rotate_right = 0;
	game->key->last_x = -1;
	game->key2 = malloc(sizeof(t_key));
	game->key2->forward = 0;
	game->key2->back = 0;
	game->key2->left = 0;
	game->key2->right = 0;
	game->key2->rotate_left = 0;
	game->key2->rotate_right = 0;
	game->key2->last_x = -1;
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

void	window_init(t_game *game)
{
	game->mlx = mlx_init();
	game->mlx_win = mlx_new_window(game->mlx, game->graphics->screen_lenght,
			game->graphics->screen_height, "cub3d");
	game->img->img = mlx_new_image(game->mlx, game->graphics->screen_lenght,
			game->graphics->screen_height);
	game->img->addr = mlx_get_data_addr(game->img->img,
			&game->img->bits_per_pixel, &game->img->line_length,
			&game->img->endian);
}

/* Setup the default values ​​of the game */
void	game_init(t_game *game, char *mode)
{
	game->cubfile = NULL;
	game->line_map = 0;
	game->gamemode = ft_atoi(mode);
	game->map = NULL;
	game->map_length = 0;
	game->map_height = 0;
	game->player = malloc(sizeof(t_player));
	game->player_two = malloc(sizeof(t_player));
	init_player(game->player);
	init_player(game->player_two);
	key_init(game);
	game->start_time = get_current_time();
	game->last_time_update = get_current_time();
	game->last_ennemi_time_update = get_current_time();
	game->enemies_count = 0;
	game->img = malloc(sizeof(t_img));
	graphic_init(game);
	window_init(game);
	sprite_init(game);
	sprite_init_bis(game);
}
