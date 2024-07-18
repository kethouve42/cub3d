/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acasanov <acasanov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 14:25:56 by kethouve          #+#    #+#             */
/*   Updated: 2024/07/18 19:48:24 by acasanov         ###   ########.fr       */
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

void free_image(t_game *game, t_img *img)
{
	if(img->img)
		mlx_destroy_image(game->mlx, img->img);
}

int	close_game(t_game *game, char *error_msg)
{
	if(error_msg)
		printf("Error\n%s\n", error_msg);

	if(game->cubfile)
		free_tab(game->cubfile);
	if(game->map)
		free_tab(game->map);
	free(game->key);

	if(game->img->img)
		mlx_destroy_image(game->mlx, game->img->img);
	free_image(game, &game->graphics->textN);
	free_image(game, &game->graphics->textS);
	free_image(game, &game->graphics->textW);
	free_image(game, &game->graphics->textE);
	free(game->graphics);
	free(game->player);
	free(game->img);

	mlx_destroy_window(game->mlx, game->mlx_win);
	mlx_destroy_display(game->mlx);
	free(game->mlx);
	printf("end\n");
	exit(0);
}

int minimap(t_game *game)
{
	int x = 0;
	int	y = 0;
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
}

int	key_press(int keycode, t_game *game)
{
	if (keycode == 65307) // Escape key
		close_game(game, NULL);
	else if (keycode == 65363) // Right arrow key
		game->key->rotate_right = 1;
	else if (keycode == 65361) // Left arrow key
		game->key->rotate_left = 1;
	else if (keycode == 119 || keycode == 122) // W/Z key (to the up)
		game->key->forward = 1;
	else if (keycode == 115) // S key (to the back)
		game->key->back = 1;
	else if (keycode == 100) // D key (to the right)
		game->key->right = 1;
	else if (keycode == 97 || keycode == 113) // A/Q key (to the left)
		game->key->left = 1;

	//printf("=== Player ===\npos : [%f:%f]\nrot : [%f:%f]\n\n", game->player->posX, game->player->posY, game->player->dirX, game->player->dirY);
	return (0);
}

int key_release(int keycode, t_game *game)
{
	if (keycode == 65363) // Right arrow key
		game->key->rotate_right = 0;
	else if (keycode == 65361) // Left arrow key
		game->key->rotate_left = 0;
	else if (keycode == 119 || keycode == 122) // W/Z key (to the up)
		game->key->forward = 0;
	else if (keycode == 115) // S key (to the back)
		game->key->back = 0;
	else if (keycode == 100) // D key (to the right)
		game->key->right = 0;
	else if (keycode == 97 || keycode == 113) // A/Q key (to the left)
		game->key->left = 0;
	return (0);
}

int player(t_game *game)
{
	int tempX;
	int tempY;
	if (game->key->rotate_right == 1) // Right arrow key
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
	if (game->key->rotate_left == 1) // Left arrow key
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
	if (game->key->forward) // W/Z key
	{
		tempX = (int)(game->player->posX + game->player->dirX * MOVE_SPEED * HITBOX_SIZE);
		tempY = (int)(game->player->posY + game->player->dirY * MOVE_SPEED * HITBOX_SIZE);
		if(game->map[tempX][tempY] == '0')
		{
			game->player->posX += game->player->dirX * MOVE_SPEED;
			game->player->posY += game->player->dirY * MOVE_SPEED;
		}
	}
	if (game->key->back) // S key
	{
		tempX = (int)(game->player->posX - game->player->dirX * MOVE_SPEED * HITBOX_SIZE);
		tempY = (int)(game->player->posY - game->player->dirY * MOVE_SPEED * HITBOX_SIZE);
		if(game->map[tempX][tempY] == '0')
		{
			game->player->posX -= game->player->dirX * MOVE_SPEED;
			game->player->posY -= game->player->dirY * MOVE_SPEED;
		}
	}
	if (game->key->right) // D key (to the right)
	{
		tempX = (int)(game->player->posX + game->player->dirY * MOVE_SPEED * HITBOX_SIZE);
    	tempY = (int)(game->player->posY - game->player->dirX * MOVE_SPEED * HITBOX_SIZE);
		if(game->map[tempX][tempY] == '0')
		{
			game->player->posX += game->player->dirY * MOVE_SPEED;
    		game->player->posY -= game->player->dirX * MOVE_SPEED;
		}
	}
	if (game->key->left) // A/Q key (to the left)
	{
		tempX = (int)(game->player->posX - game->player->dirY * MOVE_SPEED * HITBOX_SIZE);
    	tempY = (int)(game->player->posY + game->player->dirX * MOVE_SPEED * HITBOX_SIZE);
		if(game->map[tempX][tempY] == '0')
		{
			game->player->posX -= game->player->dirY * MOVE_SPEED;
	    	game->player->posY += game->player->dirX * MOVE_SPEED;
		}
	}

	draw_skyground(game);
	raycast(game);
	minimap(game);
	
	mlx_put_image_to_window(game->mlx, game->mlx_win, game->img->img, 0, 0);
	return (0);
}

int	main(int ac, char **av)
{
	t_game	game;

	if (ac != 2)
		return (1);
	{	
		game.player = malloc(sizeof(t_player));
		game.graphics = malloc(sizeof(t_graphics));
		game.key = malloc(sizeof(t_key));
		game.img = malloc(sizeof(t_img));

		game.cubfile = NULL;
		game.map = NULL;

		game.player->posX = 1;
		game.player->posY = 1;
		game.player->size = 16;
		game.player->color = 0xABC000;

		game.player->dirX = -1;
		game.player->dirY = 0;
		game.player->planeX = 0;
		game.player->planeY = 0.66;

		game.graphics->textN.img = NULL;
		game.graphics->textS.img = NULL;
		game.graphics->textE.img = NULL;
		game.graphics->textW.img = NULL;

		game.lineMap = 0;
		game.mapLength = 0;
		game.mapHeight = 0;
		game.playerStartRot = 0;

		game.key->forward = 0;
		game.key->back = 0;
		game.key->left = 0;
		game.key->right = 0;
		game.key->rotate_left = 0;
		game.key->rotate_right = 0;
		
		game.mlx = mlx_init();
		game.mlx_win = mlx_new_window(game.mlx, 24 * 64, 11 * 64, "Hello world!");
		game.img->img = mlx_new_image(game.mlx, 24 * 64, 11 * 64);
		game.img->addr = mlx_get_data_addr(game.img->img, &game.img->bits_per_pixel, &game.img->line_length,
									&game.img->endian);
	}
	map_analysis(&game, av[1]);

	draw_skyground(&game);
	raycast(&game);				
	minimap(&game);

	mlx_put_image_to_window(game.mlx, game.mlx_win, game.img->img, 0, 0);
	mlx_hook(game.mlx_win, 17, 0L, &close_game, &game);
	
	mlx_hook(game.mlx_win, 2, 1L<<0, key_press, &game);
	mlx_loop_hook(game.mlx, player, &game);
	mlx_hook(game.mlx_win, 3, 1L<<1, key_release, &game);

	mlx_loop(game.mlx);
}
