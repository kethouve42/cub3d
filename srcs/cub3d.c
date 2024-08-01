/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kethouve <kethouve@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 14:25:56 by kethouve          #+#    #+#             */
/*   Updated: 2024/08/01 19:11:20 by kethouve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_ennemie(t_game	*game)
{
	game->enemies.sprite = malloc(sizeof(t_sprite));
	game->enemies.sprite->sprite_x = 2.5;
	game->enemies.sprite->sprite_y = 9.5;
	game->enemies.sprite->s_tex = malloc(sizeof(t_img) * 2);
	game->enemies.sprite->s_tex[0].img = NULL;
	game->enemies.sprite->s_tex[1].img = NULL;
	game->enemies.sprite->index = 0;
	game->enemies.sprite->nb = 2;
	game->graphics->tmp_path = ft_strdup("texture/warrior.xpm\n");
	load_texture(game, &game->enemies.sprite->s_tex[0], game->graphics->tmp_path);
	free(game->graphics->tmp_path);
	game->graphics->tmp_path = NULL;
	game->graphics->tmp_path = ft_strdup("texture/warrior2.xpm\n");
	load_texture(game, &game->enemies.sprite->s_tex[1], game->graphics->tmp_path);
	free(game->graphics->tmp_path);
	game->graphics->tmp_path = NULL;
}

/* Setup the default values ​​of the game */
void	game_init(t_game *game)
{
	game->cubfile = NULL;
	game->line_map = 0;
	game->map = NULL;
	game->map_length = 0;
	game->map_height = 0;
	game->player = malloc(sizeof(t_player));
	game->player->pos_x = 1;
	game->player->pos_y = 1;
	game->player->dir_x = -1;
	game->player->dir_y = 0;
	game->player->plane_x = 0;
	game->player->plane_y = 0.66;
	game->player_start_rot = 0;
	game->key = malloc(sizeof(t_key));
	game->key->forward = 0;
	game->key->back = 0;
	game->key->left = 0;
	game->key->right = 0;
	game->key->shoot = 0;
	game->key->last_x = -1;
	game->start_time = get_current_time();
	game->last_time_update = get_current_time();
}

/* Setup the default values ​​of the window */
void	graphic_init(t_game *game)
{
	game->img = malloc(sizeof(t_img));
	game->graphics = malloc(sizeof(t_graphics));
	game->graphics->sprites = NULL;
	game->graphics->screen_lenght = 24 * 64;
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

	if (ac != 2)
		return (1);
	game_init(&game);
	graphic_init(&game);
	window_init(&game);
	sprite_init(&game);
	init_ennemie(&game);
	map_analysis(&game, av[1]);
	//add_enemies(&game);
	draw_skyground(&game);
	raycast(&game);
	playsound("suspense", 0, 0, 0);
	mlx_put_image_to_window(game.mlx, game.mlx_win, game.img->img, 0, 0);
	mlx_hook(game.mlx_win, 2, 1L << 0, key_press, &game);
	mlx_loop_hook(game.mlx, player, &game);
	mlx_hook(game.mlx_win, 3, 1L << 1, key_release, &game);
	mlx_hook(game.mlx_win, 17, 0L, &red_cross, &game);
	mlx_hook(game.mlx_win, 6, 1L << 6, mouse, &game);
	mlx_loop(game.mlx);
}
