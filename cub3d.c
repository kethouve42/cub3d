/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kethouve <kethouve@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 14:25:56 by kethouve          #+#    #+#             */
/*   Updated: 2024/07/10 13:56:50 by kethouve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include <unistd.h>
# include <stdlib.h>
# include "./minilibx-linux/mlx.h"
# include <stdio.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
#include <math.h>

typedef struct	s_data {
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_data;

typedef struct	s_player
{
	int	x;
	int	y;
	int	size;
	int	color;
	double	dir_x;
	double	dir_y;
	double	plane_x;
	double	plane_y;
}				t_player;

typedef struct s_game
{
	void		*mlx;
	void		*mlx_win;
	t_data		img;
	t_player	player;
}				t_game;



char *worldMap[] = {
  "111111111111111111111111",
  "100000000000000000000001",
  "100000000000000000000001",
  "100000000000000000000001",
  "100000000000000000000001",
  "100000000000100000000001",
  "100000000000100000000001",
  "100000000000100000000001",
  "100000000000100000000001",
  "100000000000100000000001",
  "111111111111111111111111",
  "\0"
};

void	my_mlx_pixel_put(t_data *data, int y, int x, int color)
{
	if (x >= 0 && x < 25 * 64 && y >= 0 && y < 11 * 64)
	{
		char	*dst;

		dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
		*(unsigned int*)dst = color;
	}
}

void	draw_square(t_data *data, int y_start, int x_start, int size, int color)
{
	int	x = 0;
	int	y = 0;
	while (y < size)
	{
		x = 0;
		while (x < size)
		{
			my_mlx_pixel_put(data, y_start + y, x_start + x, color);
			x++;
		}
		y++;
	}
}

void	draw_player(t_data *data, t_player *player)
{
	draw_square(data, player->x, player->y, player->size, player->color);
}

int	key_hook(int keycode, t_game *game)
{
	if (keycode == 65361) // Left arrow key
		game->player.y -= 5;
	if (keycode == 65362) // Up arrow key
		game->player.x -= 5;
	if (keycode == 65363) // Right arrow key
		game->player.y += 5;
	if (keycode == 65364) // Down arrow key
		game->player.x += 5;

	draw_square(&game->img, 0, 0, 25 * 64, 0x000000);
	int x = 0;
	int	y = 0;
	while (worldMap[y])
	{
		x = 0;
		while (worldMap[y][x])
		{
			if (worldMap[y][x] == '1')
				draw_square(&game->img, y * 64, x * 64, 62, 0x00F000);
			else if (worldMap[y][x] == '0')
				draw_square(&game->img, y * 64, x * 64, 62, 0x0209FF);
			x++;
		}
		y++;
	}
	draw_player(&game->img, &game->player);
	mlx_put_image_to_window(game->mlx, game->mlx_win, game->img.img, 0, 0);
	return (0);
}

int	main(void)
{
	t_game	game;
	int x = 0;
	int	y = 0;
	game.player.x = 2 * 64;
	game.player.y = 2 * 64;
	game.player.size = 20;
	game.player.color = 0xFF0000;

	game.player.dir_x = -1;
	game.player.dir_y = 0;
	game.player.plane_x = 0;
	game.player.plane_y = 0.66;
	
	game.mlx = mlx_init();
	game.mlx_win = mlx_new_window(game.mlx, 24 * 64, 11 * 64, "Hello world!");
	game.img.img = mlx_new_image(game.mlx, 24 * 64, 11 * 64);
	game.img.addr = mlx_get_data_addr(game.img.img, &game.img.bits_per_pixel, &game.img.line_length,
								&game.img.endian);
	while (worldMap[y])
	{
		x = 0;
		while (worldMap[y][x])
		{
			if (worldMap[y][x] == '1')
				draw_square(&game.img, y * 64, x * 64, 62, 0x00F000);
			else if (worldMap[y][x] == '0')
				draw_square(&game.img, y * 64, x * 64, 62, 0x0209FF);
			x++;
		}
		y++;
	}
	draw_player(&game.img, &game.player);
	mlx_put_image_to_window(game.mlx, game.mlx_win, game.img.img, 0, 0);
	mlx_key_hook(game.mlx_win, key_hook, &game);
	mlx_loop(game.mlx);
}
