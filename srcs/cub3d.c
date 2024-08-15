/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acasanov <acasanov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 14:25:56 by kethouve          #+#    #+#             */
/*   Updated: 2024/08/15 16:22:09 by acasanov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/* Setup the default values ​​of the game */
void	game_init(t_game *game, char *mode)
{
	game->cubfile = NULL;
	game->line_map = 0;
	game->gamemode = ft_atoi(mode);
	game->map = NULL;
	game->map_length = 0;
	game->map_height = 0;
////////////////////////////////////////////////////////////////////////////////
	game->player = malloc(sizeof(t_player));
	game->player->pos_x = 1;
	game->player->pos_y = 1;
	game->player->dir_x = -1;
	game->player->dir_y = 0;
	game->player->plane_x = 0;
	game->player->plane_y = 0.66;
	game->player->player_start_rot = 0;

	game->player->hp = 5;
	game->player->sprite = malloc(sizeof(t_sprite));
	game->player->sprite->s_tex = malloc(sizeof(t_img) * 2);
	game->player->sprite->s_tex[0].img = NULL;
	game->player->sprite->s_tex[1].img = NULL;
	game->player->sprite->index = 0;
	game->player->sprite->nb = 2;

////////////////////////////////////////////////////////////////////////
	game->player_two = malloc(sizeof(t_player));
	game->player_two->pos_x = 1;
	game->player_two->pos_y = 1;
	game->player_two->dir_x = -1;
	game->player_two->dir_y = 0;
	game->player_two->plane_x = 0;
	game->player_two->plane_y = 0.66;
	game->player_two->player_start_rot = 0;

	game->player_two->hp = 5;
	game->player_two->sprite = malloc(sizeof(t_sprite));
	game->player_two->sprite->s_tex = malloc(sizeof(t_img) * 2);
	game->player_two->sprite->s_tex[0].img = NULL;
	game->player_two->sprite->s_tex[1].img = NULL;
	game->player_two->sprite->index = 0;
	game->player_two->sprite->nb = 2;

////////////////////////////////////////////////////////////////////////
	game->key = malloc(sizeof(t_key));
	game->key->forward = 0;
	game->key->back = 0;
	game->key->left = 0;
	game->key->right = 0;
	game->key->last_x = -1;
	game->key2 = malloc(sizeof(t_key));
	game->key2->forward = 0;
	game->key2->back = 0;
	game->key2->left = 0;
	game->key2->right = 0;
	game->key2->last_x = -1;
	game->start_time = get_current_time();
	game->last_time_update = get_current_time();
	game->last_ennemi_time_update = get_current_time();
	game->enemies_count = 0;
}

/* Setup the default values ​​of the window */
void	graphic_init(t_game *game)
{
	game->img = malloc(sizeof(t_img));
	game->graphics = malloc(sizeof(t_graphics));
	game->graphics->sprites = NULL;
	game->graphics->screen_lenght = 24 * 64;
	if (game->gamemode == 2)
		game->graphics->screen_lenght += 24 * 64 + 10;
	game->graphics->screen_height = 13 * 64;
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
	game->graphics->s_pillar.img = NULL;
	game->graphics->s_barrel.img = NULL;
	game->graphics->tex_door.img = NULL;
	game->graphics->tex_door2.img = NULL;
	game->graphics->s_enemi_one.img = NULL;
	game->graphics->s_enemi_two.img = NULL;
	game->graphics->s_enemi_dead.img = NULL;
	game->graphics->sprite_count = 0;
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

/* Retrieve all information from the .cub file */
void	map_analysis(t_game *game, char *map_path)
{
	int	file_size;
	int	i;

	i = ft_strlen(map_path) - 1;
	if (map_path[i] != 'b' || map_path[i - 1] != 'u'
		|| map_path[i - 2] != 'c' || map_path[i - 3] != '.')
		close_game(game, "need a .cub file");
	file_size = get_lines(game, map_path);
	game->cubfile = copy_map(map_path, game, file_size, 0);
	check_graphics(game);
	check_map(game, map_path, file_size);
	check_path(game, map_path, file_size);
}

int	main(int ac, char **av)
{
	t_game	game;

	if (ac != 3)
		return (1);
	game_init(&game, av[2]);
	graphic_init(&game);
	window_init(&game);
	sprite_init(&game);
	map_analysis(&game, av[1]);
	draw_skyground(&game);

	game.player->sprite->s_tex[0] = game.graphics->s_enemi_one;
	game.player->sprite->s_tex[1] = game.graphics->s_enemi_two;
	game.player_two->sprite->s_tex[0] = game.graphics->s_enemi_one;
	game.player_two->sprite->s_tex[1] = game.graphics->s_enemi_two;

	game.player->sprite->sprite_x = game.player->pos_x;
	game.player->sprite->sprite_y = game.player->pos_y;
	if (game.gamemode == 2)
	{
		game.player_two->sprite->sprite_x = game.player_two->pos_x;
		game.player_two->sprite->sprite_y = game.player_two->pos_y;

		raycast(&game, game.player, 0, game.graphics->screen_lenght / 2 - 5);
		raycast(&game, game.player_two, game.graphics->screen_lenght / 2 + 5, game.graphics->screen_lenght);
	}
	else
		raycast(&game, game.player, 0, game.graphics->screen_lenght);
	mlx_put_image_to_window(game.mlx, game.mlx_win, game.img->img, 0, 0);
	playsound("suspense", 0, 0, 0);
	mlx_hook(game.mlx_win, 2, 1L << 0, key_press, &game);
	mlx_loop_hook(game.mlx, player, &game);
	mlx_hook(game.mlx_win, 3, 1L << 1, key_release, &game);
	mlx_hook(game.mlx_win, 17, 0L, &red_cross, &game);
	if (game.gamemode == 1)
		mlx_hook(game.mlx_win, 6, 1L << 6, mouse, &game);
	mlx_loop(game.mlx);
}
