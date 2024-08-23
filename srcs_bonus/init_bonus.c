/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acasanov <acasanov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 18:47:52 by acasanov          #+#    #+#             */
/*   Updated: 2024/08/23 16:12:26 by acasanov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

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
	player->sprite_buff = 0;
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

void	get_enemie(t_game *game, char **map, int x, int y)
{
	t_enemie	*enemie;

	enemie = malloc(sizeof(t_enemie));
	enemie->hp = 3;
	enemie->n_move = 3000;
	enemie->move = enemie->n_move;
	enemie->move_state = 1;
	enemie->chase_status = 0;
	enemie->sprite = malloc(sizeof(t_sprite));
	enemie->sprite->sprite_x = y + 0.5;
	enemie->sprite->sprite_y = x + 0.5;
	enemie->sprite->s_tex = malloc(sizeof(t_img) * 3);
	enemie->sprite->s_tex[0].img = NULL;
	enemie->sprite->s_tex[1].img = NULL;
	enemie->sprite->s_tex[2].img = NULL;
	enemie->sprite->index = 0;
	enemie->sprite->nb = 3;
	enemie->sprite->s_tex[0] = game->graphics->s_enemi_one;
	enemie->sprite->s_tex[1] = game->graphics->s_enemi_two;
	enemie->sprite->s_tex[2] = game->graphics->s_enemi_dead;
	map[y][x] = '0';
	game->enemies[game->enemies_count] = enemie;
	game->enemies_count++;
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
	game->enemies = NULL;
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
	sprite_init_ter(game);
}
