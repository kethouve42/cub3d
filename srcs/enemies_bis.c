/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enemies_bis.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acasanov <acasanov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 16:09:54 by acasanov          #+#    #+#             */
/*   Updated: 2024/08/21 16:11:12 by acasanov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ennemie_routine_bis(t_game *game, t_enemie *enemie,
	int temp_x, int temp_y)
{
	if (enemie->move_state == 1)
	{
		temp_x = (int)(enemie->sprite->sprite_x - 0.01 - 0.15);
		if (is_into_str(game->map[temp_x][temp_y], "1PDB") == 0)
			enemie->sprite->sprite_x -= 0.01;
		else
		{
			enemie->move = enemie->n_move + 1;
			enemie->move_state = 2;
		}
	}
	else if (enemie->move_state == 2)
	{
		temp_y = (int)(enemie->sprite->sprite_y - 0.01 - 0.15);
		if (is_into_str(game->map[temp_x][temp_y], "1PDB") == 0)
			enemie->sprite->sprite_y -= 0.01;
		else
		{
			enemie->move = enemie->n_move + 1;
			enemie->move_state = 3;
		}
	}
}

void	ennemie_routine_ter(t_game *game, t_enemie *enemie,
	int temp_x, int temp_y)
{
	if (enemie->move_state == 3)
	{
		temp_x = (int)(enemie->sprite->sprite_x + 0.01 + 0.15);
		if (is_into_str(game->map[temp_x][temp_y], "1PDB") == 0)
			enemie->sprite->sprite_x += 0.01;
		else
		{
			enemie->move = enemie->n_move + 1;
			enemie->move_state = 4;
		}
	}
	else if (enemie->move_state == 4)
	{
		temp_y = (int)(enemie->sprite->sprite_y + 0.01 + 0.15);
		if (is_into_str(game->map[temp_x][temp_y], "1PDB") == 0)
			enemie->sprite->sprite_y += 0.01;
		else
		{
			enemie->move = enemie->n_move + 1;
			enemie->move_state = 1;
		}
	}
}

void	ennemie_routine(t_game *game, t_enemie *enemie)
{
	int	temp_y;
	int	temp_x;

	temp_x = (int)enemie->sprite->sprite_x;
	temp_y = (int)enemie->sprite->sprite_y;
	ennemie_routine_bis(game, enemie, temp_x, temp_y);
	ennemie_routine_ter(game, enemie, temp_x, temp_y);
	enemie->move--;
	if (enemie->move == 0)
	{
		enemie->move = enemie->n_move;
		if (enemie->move_state == 1)
			enemie->move_state = 2;
		else if (enemie->move_state == 2)
			enemie->move_state = 3;
		else if (enemie->move_state == 3)
			enemie->move_state = 4;
		else
			enemie->move_state = 1;
	}
	detection(game, enemie);
}

void	chase_bis(t_game *game, t_enemie *enemie, t_player *target)
{
	int	temp_x;
	int	temp_y;

	temp_x = enemie->sprite->sprite_x;
	temp_y = enemie->sprite->sprite_y;
	if (enemie->sprite->sprite_y < target->pos_y)
	{
		temp_y = (int)enemie->sprite->sprite_y + 0.02 * HITBOX_SIZE;
		if (is_into_str(game->map[temp_x][temp_y], "1PDB") == 0)
			enemie->sprite->sprite_y += 0.02;
	}
	if (enemie->sprite->sprite_y > target->pos_y)
	{
		temp_y = (int)enemie->sprite->sprite_y - 0.02 * HITBOX_SIZE;
		if (is_into_str(game->map[temp_x][temp_y], "1PDB") == 0)
			enemie->sprite->sprite_y -= 0.02;
	}
}

void	chase(t_game *game, t_enemie *enemie, t_player *target)
{
	int	temp_x;
	int	temp_y;

	temp_x = enemie->sprite->sprite_x;
	temp_y = enemie->sprite->sprite_y;
	if (enemie->sprite->sprite_x > target->pos_x)
	{
		temp_x = (int)enemie->sprite->sprite_x - 0.02 * HITBOX_SIZE;
		if (is_into_str(game->map[temp_x][temp_y], "1PDB") == 0)
			enemie->sprite->sprite_x -= 0.02;
	}
	if (enemie->sprite->sprite_x < target->pos_x)
	{
		temp_x = (int)enemie->sprite->sprite_x + 0.02 * HITBOX_SIZE;
		if (is_into_str(game->map[temp_x][temp_y], "1PDB") == 0)
			enemie->sprite->sprite_x += 0.02;
	}
	chase_bis(game, enemie, target);
}
