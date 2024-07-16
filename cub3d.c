/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kethouve <kethouve@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 14:25:56 by kethouve          #+#    #+#             */
/*   Updated: 2024/07/16 23:45:33 by kethouve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "cub3d.h"



void	my_mlx_pixel_put(t_img *img, int y, int x, int color)
{
	char	*dst;

	dst = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

void	draw_square(t_img *img, int y_start, int x_start, int size, int color)
{
	int	x = 0;
	int	y = 0;
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
	draw_square(img, player->posX * 16, player->posY * 16, player->size, player->color);
}

int	close_game(t_game *game)
{
	// surement faut free des trucs avant
	mlx_destroy_window(game->mlx, game->mlx_win);
	mlx_destroy_display(game->mlx);
	free(game->mlx);
	exit(0);
}

int	key_hook(int keycode, t_game *game)
{
	if (keycode == 65307) // Escape key
		close_game(game);
	if (keycode == 65363) // Right arrow key
	{
		// Calculer la nouvelle direction après rotation à gauche
		double oldDirX = game->player->dirX;
        game->player->dirX = game->player->dirX * cos(-ROT_SPEED) - game->player->dirY * sin(-ROT_SPEED);
        game->player->dirY = oldDirX * sin(-ROT_SPEED) + game->player->dirY * cos(-ROT_SPEED);

        // Calculer le nouveau plan de la caméra
        double oldPlaneX = game->player->planeX;
        game->player->planeX = game->player->planeX * cos(-ROT_SPEED) - game->player->planeY * sin(-ROT_SPEED);
        game->player->planeY = oldPlaneX * sin(-ROT_SPEED) + game->player->planeY * cos(-ROT_SPEED);
	}
	if (keycode == 65361) // Left arrow key
	{
		// Calculer la nouvelle direction après rotation à droite
        double oldDirX = game->player->dirX;
        game->player->dirX = game->player->dirX * cos(ROT_SPEED) - game->player->dirY * sin(ROT_SPEED);
        game->player->dirY = oldDirX * sin(ROT_SPEED) + game->player->dirY * cos(ROT_SPEED);

        // Calculer le nouveau plan de la caméra
        double oldPlaneX = game->player->planeX;
        game->player->planeX = game->player->planeX * cos(ROT_SPEED) - game->player->planeY * sin(ROT_SPEED);
        game->player->planeY = oldPlaneX * sin(ROT_SPEED) + game->player->planeY * cos(ROT_SPEED);
	}
	if (keycode == 65362) // Up arrow key
	{
		game->player->posX += game->player->dirX * 0.5;
		game->player->posY += game->player->dirY * 0.5;
	}
	if (keycode == 65364) // Down arrow key
	{
		game->player->posX -= game->player->dirX * 0.5;
		game->player->posY -= game->player->dirY * 0.5;
	}

	printf("=== Player ===\npos : [%f:%f]\nrot : [%f:%f]\n", game->player->posX, game->player->posY, game->player->dirX, game->player->dirY);


	draw_skyground(game);
	raycast(game);

	int x = 0;
	int	y = 0;
	while (y < 11)
	{
		x = 0;
		while (game->map[y][x])
		{
			draw_square(&game->img, y * 16, x * 16, 16, 0x000000);
			if (game->map[y][x] == '1')
				draw_square(&game->img, y * 16, x * 16, 15, 0x00F000);
			else if (game->map[y][x] == '0')
				draw_square(&game->img, y * 16, x * 16, 15, 0x0209FF);
			x++;
		}
		y++;
	}
	draw_player(&game->img, game->player);

	mlx_put_image_to_window(game->mlx, game->mlx_win, game->img.img, 0, 0);
	return (0);
}

int	main(int ac, char **av)
{
	t_game	game;

	if (ac != 2)
		return (1);

	game.player = malloc(sizeof(t_player));
	game.graphics = malloc(sizeof(t_graphics));

	game.player->posX = 6;
	game.player->posY = 3;
	game.player->size = 16;
	game.player->color = 0xABC000;

	game.player->dirX = -1;
	game.player->dirY = 0;
	game.player->planeX = 0;
	game.player->planeY = 0.66;

	char *la_map[] = {
	"111111111111111111111111\0",
	"100000000000000000000001\0",
	"100000000000000000000001\0",
	"100000000000000000000001\0",
	"100000000000000000000001\0",
	"100000000000100000000001\0",
	"100000000000100000000001\0",
	"100000000000100000000001\0",
	"100000000000100000000001\0",
	"100000000000100000000001\0",
	"111111111111111111111111\0",
	"\0"
	};
	
	game.map = la_map;

	//game.screenHeight = 11 * 64;
	//game.screenWidth = 24 * 64;
	
	game.mlx = mlx_init();
	game.mlx_win = mlx_new_window(game.mlx, 24 * 64, 11 * 64, "Hello world!");
	game.img.img = mlx_new_image(game.mlx, 24 * 64, 11 * 64);
	game.img.addr = mlx_get_data_addr(game.img.img, &game.img.bits_per_pixel, &game.img.line_length,
								&game.img.endian);

	map_analysis(&game, av[1]);

	draw_skyground(&game);
	raycast(&game);
								
	int x = 0;
	int	y = 0;
	while (y < 11)
	{
		x = 0;
		while (la_map[y][x])
		{
			//printf("[%d : %d]\n", x, y);
			draw_square(&game.img, y * 16, x * 16, 16, 0x000000);
			if (la_map[y][x] == '1')
				draw_square(&game.img, y * 16, x * 16, 15, 0x00F000);
			else if (la_map[y][x] == '0')
				draw_square(&game.img, y * 16, x * 16, 15, 0x0209FF);
			x++;
		}
		y++;
	}
	draw_player(&game.img, game.player);

	mlx_put_image_to_window(game.mlx, game.mlx_win, game.img.img, 0, 0);
	mlx_key_hook(game.mlx_win, key_hook, &game);
	mlx_loop(game.mlx);
}
