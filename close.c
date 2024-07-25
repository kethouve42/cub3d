/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acasanov <acasanov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 19:48:13 by acasanov          #+#    #+#             */
/*   Updated: 2024/07/25 16:58:27 by acasanov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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
	free_texture(game, &game->graphics->tex_n);
	free_texture(game, &game->graphics->tex_s);
	free_texture(game, &game->graphics->tex_e);
	free_texture(game, &game->graphics->tex_w);
	free(game->graphics->sprites);
	if (game->graphics->tmp_path != NULL)
		free(game->graphics->tmp_path);
	free(game->graphics);
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
	free(game->z_buffer);
	if (game->img->img)
		mlx_destroy_image(game->mlx, game->img->img);
	free_graphics(game);
	free(game->player);
	free(game->img);
	mlx_destroy_window(game->mlx, game->mlx_win);
	mlx_destroy_display(game->mlx);
	free(game->mlx);
	printf("End\n");
	exit(0);
}
