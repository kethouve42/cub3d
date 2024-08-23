/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kethouve <kethouve@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 19:48:13 by acasanov          #+#    #+#             */
/*   Updated: 2024/08/23 15:55:10 by kethouve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	free_texture(t_game *game, t_texture *tex)
{
	int	i;

	i = 0;
	while (i < tex->nb)
	{
		if (tex->tex[i].img)
			mlx_destroy_image(game->mlx, tex->tex[i].img);
		i++;
	}
	free(tex->tex);
}

void	free_tab(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

int	red_cross(t_game *game)
{
	close_game(game, NULL);
}

void	free_graphics(t_game *game)
{
	if (game->graphics->s_barrel.img)
		mlx_destroy_image(game->mlx, game->graphics->s_barrel.img);
	if (game->graphics->s_pillar.img)
		mlx_destroy_image(game->mlx, game->graphics->s_pillar.img);
	if (game->graphics->tex_door.img)
		mlx_destroy_image(game->mlx, game->graphics->tex_door.img);
	if (game->graphics->tex_door2.img)
		mlx_destroy_image(game->mlx, game->graphics->tex_door2.img);
	if (game->graphics->s_enemi_one.img)
		mlx_destroy_image(game->mlx, game->graphics->s_enemi_one.img);
	if (game->graphics->s_enemi_two.img)
		mlx_destroy_image(game->mlx, game->graphics->s_enemi_two.img);
	if (game->graphics->s_enemi_dead.img)
		mlx_destroy_image(game->mlx, game->graphics->s_enemi_dead.img);
	free_texture(game, &game->graphics->tex_n);
	free_texture(game, &game->graphics->tex_s);
	free_texture(game, &game->graphics->tex_e);
	free_texture(game, &game->graphics->tex_w);
	if (game->graphics->sprites)
		free(game->graphics->sprites);
	if (game->graphics->tmp_path != NULL)
		free(game->graphics->tmp_path);
	free(game->graphics);
}

/* Free everything that has been allocated and exit the program */
int	close_game(t_game *game, char *error_msg)
{
	playsound("shotgun", 0, 1, 0);
	if (error_msg)
		printf("Error\n%s\n", error_msg);
	free_sprite(game);
	if (game->cubfile)
		free_tab(game->cubfile);
	if (game->map)
		free_tab(game->map);
	free(game->key);
	free(game->key2);
	free(game->z_buffer);
	if (game->img->img)
		mlx_destroy_image(game->mlx, game->img->img);
	free_enemie(game);
	free_player_img(game);
	free_graphics(game);
	free_player(game);
	free(game->img);
	mlx_destroy_window(game->mlx, game->mlx_win);
	mlx_destroy_display(game->mlx);
	free(game->mlx);
	printf("End\n");
	exit(0);
}
