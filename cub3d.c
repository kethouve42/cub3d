/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acasanov <acasanov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 14:25:56 by kethouve          #+#    #+#             */
/*   Updated: 2024/07/20 20:01:07 by acasanov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	my_mlx_pixel_put(t_img *img, int y, int x, int color)
{
	char	*dst;

	dst = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

/*void	draw_square(t_img *img, int y_start, int x_start, int size, int color)
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
}*/

/*void	draw_player(t_img *img, t_player *player)
{
	draw_square(img, player->posX * 16, player->posY * 16,
		player->size, player->color);
}*/

/*int	minimap(t_game *game)
{
	int	x;
	int	y;

	x = 0;
	y = 0;
	while (y < game->mapHeight)
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
}*/

void	free_image(t_game *game, t_img *img)
{
	if (img->img)
		mlx_destroy_image(game->mlx, img->img);
}

/* Free everything that has been allocated and exit the program */
int	close_game(t_game *game, char *error_msg)
{
	if (error_msg)
		printf("Error\n%s\n", error_msg);
	if (game->cubfile)
		free_tab(game->cubfile);
	if (game->map)
		free_tab(game->map);
	free(game->key);
	if (game->img->img)
		mlx_destroy_image(game->mlx, game->img->img);
	free_image(game, &game->graphics->text_n);
	free_image(game, &game->graphics->text_s);
	free_image(game, &game->graphics->text_e);
	free_image(game, &game->graphics->text_w);
	free(game->graphics);
	free(game->player);
	free(game->img);
	mlx_destroy_window(game->mlx, game->mlx_win);
	mlx_destroy_display(game->mlx);
	free(game->mlx);
	printf("End\n");
	exit(0);
}

/* Update player placements and display
   The speed is divided by 2 in case of diagonal movement */
//! Si 2 touches laterales pressees, on peut avancer/reculer, mais pas l'inverse
int	player(t_game *game)
{
	double	old_dir_x;
	double	old_plane_x;
	int		temp_x;
	int		temp_y;

	old_dir_x = game->player->dir_x;
	old_plane_x = game->player->plane_x;
	player_rotation(game, old_dir_x, old_plane_x);
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
	mlx_put_image_to_window(game->mlx, game->mlx_win, game->img->img, 0, 0);
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
	game->key->rotate_left = 0;
	game->key->rotate_right = 0;
}

/* Setup the default values ​​of the window */
void	graphic_init(t_game *game)
{
	game->img = malloc(sizeof(t_img));
	game->graphics = malloc(sizeof(t_graphics));
	game->graphics->screen_lenght = 24 * 64;
	game->graphics->screen_height = 11 * 64;
	game->graphics->text_n.img = NULL;
	game->graphics->text_s.img = NULL;
	game->graphics->text_e.img = NULL;
	game->graphics->text_w.img = NULL;
	game->mlx = mlx_init();
	game->mlx_win = mlx_new_window(game->mlx, game->graphics->screen_lenght,
			game->graphics->screen_height, "cub3d");
	game->img->img = mlx_new_image(game->mlx, game->graphics->screen_lenght,
			game->graphics->screen_height);
	game->img->addr = mlx_get_data_addr(game->img->img,
			&game->img->bits_per_pixel, &game->img->line_length,
			&game->img->endian);
}

int	main(int ac, char **av)
{
	t_game	game;

	if (ac != 2)
		return (1);
	game_init(&game);
	graphic_init(&game);
	map_analysis(&game, av[1]);
	draw_skyground(&game);
	raycast(&game);
	mlx_put_image_to_window(game.mlx, game.mlx_win, game.img->img, 0, 0);
	mlx_hook(game.mlx_win, 17, 0L, &close_game, &game);
	mlx_hook(game.mlx_win, 2, 1L << 0, key_press, &game);
	mlx_loop_hook(game.mlx, player, &game);
	mlx_hook(game.mlx_win, 3, 1L << 1, key_release, &game);
	mlx_loop(game.mlx);
}
