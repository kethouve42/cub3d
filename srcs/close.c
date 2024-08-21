/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acasanov <acasanov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 19:48:13 by acasanov          #+#    #+#             */
/*   Updated: 2024/07/21 20:33:23 by acasanov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	free_image(t_game *game, t_img *img)
{
	if (img->img)
		mlx_destroy_image(game->mlx, img->img);
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
