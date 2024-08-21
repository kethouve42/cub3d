/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acasanov <acasanov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 22:00:50 by kethouve          #+#    #+#             */
/*   Updated: 2024/08/21 19:45:09 by acasanov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	update_sprite_player(t_game *game)
{
	if (game->player->sprite->index % 2 == 1)
		game->player->sprite_buff = 0;
	else
		game->player->sprite_buff = 1;
	if (game->player_two->sprite->index % 2 == 1)
		game->player_two->sprite_buff = 0;
	else
		game->player_two->sprite_buff = 1;
}

void	swap_sprite(t_sprite *a, t_sprite *b)
{
	t_sprite	temp;

	temp = *a;
	*a = *b;
	*b = temp;
}

void	sprite_sort(t_graphics *graphics, t_game *game, t_player *player)
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
			dist1 = sqrt(pow(graphics->sprites[j]->sprite_x - player->pos_x, 2)
					+ pow(graphics->sprites[j]->sprite_y - player->pos_y, 2));
			dist2 = sqrt(pow(graphics->sprites[j + 1]->sprite_x
						- player->pos_x, 2) + pow(graphics->sprites[j + 1]
						->sprite_y - player->pos_y, 2));
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
