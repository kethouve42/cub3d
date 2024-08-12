/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kethouve <kethouve@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 22:00:50 by kethouve          #+#    #+#             */
/*   Updated: 2024/08/11 00:17:09 by kethouve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	swap_sprite(t_sprite *a, t_sprite *b)
{
	t_sprite	temp;

	temp = *a;
	*a = *b;
	*b = temp;
}

void	sprite_sort(t_graphics *graphics, t_game *game)
{
	double	dist1;
	double	dist2;
	int		i;
	int		j;

	i = 0;
	while (i < graphics->sprite_count - 1)
	{
		j = 0;
		while (j < graphics->sprite_count - i - 1)
		{
			dist1 = sqrt(pow(graphics->sprites[j]->sprite_x - game->player->pos_x, 2)
					+ pow(graphics->sprites[j]->sprite_y - game->player->pos_y, 2));
			dist2 = sqrt(pow(graphics->sprites[j + 1]->sprite_x - game->player->pos_x, 2)
					+ pow(graphics->sprites[j + 1]->sprite_y - game->player->pos_y, 2));
			if (dist1 < dist2)
				swap_sprite(graphics->sprites[j], graphics->sprites[j + 1]);
			j++;
		}
		i++;
	}
}

void	get_sprite(t_game *game, char **map, int x, int y)
{
	t_sprite	*sprite;

	sprite = malloc(sizeof(t_sprite));
	sprite->s_tex = malloc(sizeof(t_img));
	sprite->index = 0;
	sprite->nb = 1;
	if (map[y][x] == 'B')
		sprite->s_tex[0] = game->graphics->s_barrel;
	else if (map[y][x] == 'P')
		sprite->s_tex[0] = game->graphics->s_pillar;
	sprite->sprite_x = y + 0.5;
	sprite->sprite_y = x + 0.5;
	sprite->size = 16;
	game->graphics->sprites[game->graphics->sprite_count] = sprite;
	game->graphics->sprite_count++;
}

void	sprite_init(t_game *game)
{
	int	i;

	i = 0;
	game->z_buffer = (double *)malloc(sizeof(double)
			* (game->graphics->screen_lenght));
	while (i < game->graphics->screen_lenght)
	{
		game->z_buffer[i] = 0;
		i++;
	}
	game->graphics->tmp_path = ft_strdup("texture/pillar.xpm\n");
	load_texture(game, &game->graphics->s_pillar, game->graphics->tmp_path);
	free(game->graphics->tmp_path);
	game->graphics->tmp_path = NULL;
	game->graphics->tmp_path = ft_strdup("texture/barrel.xpm\n");
	load_texture(game, &game->graphics->s_barrel, game->graphics->tmp_path);
	free(game->graphics->tmp_path);
	game->graphics->tmp_path = NULL;
	game->graphics->tmp_path = ft_strdup("texture/door1.xpm\n");
	load_texture(game, &game->graphics->tex_door, game->graphics->tmp_path);
	free(game->graphics->tmp_path);
	game->graphics->tmp_path = NULL;
	game->graphics->tmp_path = ft_strdup("texture/door3.xpm\n");
	load_texture(game, &game->graphics->tex_door2, game->graphics->tmp_path);
	free(game->graphics->tmp_path);
	game->graphics->tmp_path = NULL;
}
