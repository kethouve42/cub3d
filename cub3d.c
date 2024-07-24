/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kethouve <kethouve@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 14:25:56 by kethouve          #+#    #+#             */
/*   Updated: 2024/07/25 00:39:36 by kethouve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/* ========================================================================== */
/* ================================ MINIMAP ================================= */
/* ========================================================================== */
/* =========== These 3 functions allow the display of the minimap =========== */
/* ============== Call minimap(game) in player() to display it ============== */
/* ========================================================================== */

void	draw_circle(t_img *img, int y_center, int x_center, int radius, int color)
{
	int	x;
	int	y;
	int radius_squared;

	radius_squared = radius * radius;
	y = -radius;
	while (y <= radius)
	{
		x = -radius;
		while (x <= radius)
		{
			if (x * x + y * y <= radius_squared)
				my_mlx_pixel_put(img, y_center + y, x_center + x, color);
			x++;
		}
		y++;
	}
}

void	draw_square(t_img *img, int y_start, int x_start, int size, int color)
{
	int	x;
	int	y;

	x = 0;
	y = 0;
	while (y < size)
	{
		x = 0;
		while (x < size)
		{
			my_mlx_pixel_put(img, y_start + y, x_start + x, color);
			x++;
		}
		y++;
	}
}

void	draw_player(t_img *img, t_player *player)
{
	draw_circle(img, player->pos_x * 16, player->pos_y * 16, 5, 0x80d402);
}

int	minimap(t_game *game)
{
	int	x;
	int	y;

	x = 0;
	y = 0;
	while (y < game->map_height)
	{
		x = 0;
		while (game->map[y][x])
		{
			if (game->map[y][x] == '1')
			{
				draw_square(game->img, y * 16, x * 16, 16, 0x000000);
				draw_square(game->img, y * 16, x * 16, 15, 0x00F000);
			}
			else if (game->map[y][x] == '0')
			{
				draw_square(game->img, y * 16, x * 16, 16, 0x000000);
				draw_square(game->img, y * 16, x * 16, 15, 0x0209FF);
			}
			x++;
		}
		y++;
	}
	draw_player(game->img, game->player);
}

/* Update player placements and display
   The speed is divided by 2 in case of diagonal movement */
//! Si 2 touches laterales pressees, on peut avancer/reculer, mais pas l'inverse
int	player(t_game *game)
{
	int		temp_x;
	int		temp_y;

	if (game->key->left + game->key->right == 1)
		player_forward_back(game, MOVE_SPEED / 2, temp_x, temp_y);
	else
		player_forward_back(game, MOVE_SPEED, temp_x, temp_y);
	if (game->key->forward + game->key->back == 1)
		player_right_left(game, MOVE_SPEED / 2, temp_x, temp_y);
	else
		player_right_left(game, MOVE_SPEED, temp_x, temp_y);
	draw_skyground(game);
	raycast(game);
	minimap(game);
	mlx_put_image_to_window(game->mlx, game->mlx_win, game->img->img, 0, 0);
	update_all_sprites_index(game);
	return (0);
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
	game->key->last_x = -1;
	game->start_time = get_current_time();
	game->last_time_update = get_current_time();
}

/* Setup the default values ​​of the window */
void	graphic_init(t_game *game)
{
	game->img = malloc(sizeof(t_img));
	game->graphics = malloc(sizeof(t_graphics));
	//game->graphics->screen_lenght = 24 * 64;
	//game->graphics->screen_height = 13 * 64;
	game->graphics->tex_n.index = 0;
	game->graphics->tex_s.index = 0;
	game->graphics->tex_e.index = 0;
	game->graphics->tex_w.index = 0;
	game->graphics->sprite_count = 0;
	game->mlx = mlx_init();
	mlx_get_screen_size(game->mlx, &game->graphics->screen_lenght, &game->graphics->screen_height);
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
	sprite_init(&game);
	map_analysis(&game, av[1]);
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
