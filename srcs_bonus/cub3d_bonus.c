/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kethouve <kethouve@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 14:25:56 by kethouve          #+#    #+#             */
/*   Updated: 2024/08/23 15:04:47 by kethouve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	update_graphics(t_game *game)
{
	draw_skyground(game);
	if (game->gamemode == 2)
	{
		raycast(game, game->player, 0, game->graphics->screen_lenght / 2 - 5);
		raycast(game, game->player_two, game->graphics->screen_lenght / 2 + 5,
			game->graphics->screen_lenght);
	}
	else
		raycast(game, game->player, 0, game->graphics->screen_lenght);
	minimap(game);
	mlx_put_image_to_window(game->mlx, game->mlx_win, game->img->img, 0, 0);
	update_all_sprites_index(game);
}

void	select_raycast(t_game *game)
{
	if (game->gamemode == 2)
	{
		raycast(game, game->player, 0, game->graphics->screen_lenght / 2 - 5);
		raycast(game, game->player_two, game->graphics->screen_lenght / 2 + 5,
			game->graphics->screen_lenght);
	}
	else
		raycast(game, game->player, 0, game->graphics->screen_lenght);
}

void	sprite_player(t_game *game, t_player *player)
{
	player->sprite->s_tex[0] = game->graphics->s_pl_face1;
	player->sprite->s_tex[1] = game->graphics->s_pl_face2;
	player->sprite->s_tex[2] = game->graphics->s_pl_left1;
	player->sprite->s_tex[3] = game->graphics->s_pl_left2;
	player->sprite->s_tex[4] = game->graphics->s_pl_right1;
	player->sprite->s_tex[5] = game->graphics->s_pl_right2;
	player->sprite->s_tex[6] = game->graphics->s_pl_back1;
	player->sprite->s_tex[7] = game->graphics->s_pl_back2;
	player->sprite->sprite_x = player->pos_x;
	player->sprite->sprite_y = player->pos_y;
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
	sprite_player(game, game->player);
	sprite_player(game, game->player_two);
	draw_skyground(game);
}

int	main(int ac, char **av)
{
	t_game	game;

	if (ac != 3 && ac != 2)
		return (1);
	if ((ac == 3))
		game_init(&game, av[2]);
	else
		game_init(&game, "1");
	map_analysis(&game, av[1]);
	select_raycast(&game);
	mlx_put_image_to_window(game.mlx, game.mlx_win, game.img->img, 0, 0);
	playsound("music", 0, 0, 0);
	mlx_hook(game.mlx_win, 2, 1L << 0, key_press, &game);
	mlx_loop_hook(game.mlx, player, &game);
	mlx_hook(game.mlx_win, 3, 1L << 1, key_release, &game);
	mlx_hook(game.mlx_win, 17, 0L, &red_cross, &game);
	if (game.gamemode == 1)
		mlx_hook(game.mlx_win, 6, 1L << 6, mouse, &game);
	mlx_loop(game.mlx);
}
