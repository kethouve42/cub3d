/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enemies.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acasanov <acasanov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 18:25:28 by acasanov          #+#    #+#             */
/*   Updated: 2024/08/20 17:11:14 by acasanov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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

void	swap_enemies(t_enemie *a, t_enemie *b)
{
	t_enemie	temp;

	temp = *a;
	*a = *b;
	*b = temp;
}

void	enemies_sort(t_enemie **enemies, t_game *game, t_player *player)
{
	double	dist1;
	double	dist2;
	int		i;
	int		j;

	i = 0;
	while (i < game->enemies_count - 1)
	{
		j = 0;
		while (j < game->enemies_count - i - 1)
		{
			dist1 = sqrt(pow(enemies[j]->sprite->sprite_x - player->pos_x, 2)
					+ pow(enemies[j]->sprite->sprite_y - player->pos_y, 2));
			dist2 = sqrt(pow(enemies[j + 1]->sprite->sprite_x - player->pos_x, 2)
					+ pow(enemies[j + 1]->sprite->sprite_y - player->pos_y, 2));
			if (dist1 < dist2)
				swap_enemies(enemies[j], enemies[j + 1]);
			j++;
		}
		i++;
	}
}

void	draw_ennemies(t_game *game, t_sprite *enemie, t_player *player, int begin)
{
	t_ray_tex	ray_tex;
	t_sprite	*sprite;

	sprite = enemie;
	ray_tex.tex = &sprite->s_tex[sprite->index];
	draw_sprite_part_one(game, &ray_tex, sprite, player);
	draw_sprite_part_two(game, &ray_tex, ray_tex.tex, begin);
}

/* 1 = Nord, 2 = Est, 3 = Sud, 4 = Ouest */
/*int	how_he_look(t_player *player)
{
	if (player->dir_x <= -0.5 && -0.5 <= player->dir_y && player->dir_y <= 0.5)
		return (1);
	else if (-0.5 <= player->dir_x && player->dir_x <= 0.5 && player->dir_y >= 0.5)
		return (2);
	else if (player->dir_x >= 0.5 && -0.5 <= player->dir_y && player->dir_y <= 0.5)
		return (3);
	else
		return (4);
}*/

/* 1 = dos, 2 = flanc droit, 3 = face, 4 = flanc gauche */
/*int	what_he_see(int look, t_player *opponent)
{
	if (look == how_he_look(opponent))
		return (1);
	if (look == 1)
	{
		if (how_he_look(opponent) == 2)
			return (2);
		else if (how_he_look(opponent) == 3)
			return (3);
		else
			return (4);
	}
	else if (look == 2)
	{
		if (how_he_look(opponent) == 1)
			return (4);
		else if (how_he_look(opponent) == 3)
			return (2);
		else
			return (3);
	}
	else if (look == 3)
	{
		if (how_he_look(opponent) == 1)
			return (3);
		else if (how_he_look(opponent) == 2)
			return (4);
		else
			return (2);
	}
	else
	{
		if (how_he_look(opponent) == 1)
			return (2);
		else if (how_he_look(opponent) == 2)
			return (3);
		else
			return (4);
	}

}*/

// angle1 and 2 = atan2 retourne l'angle entre -π et π en radians
// result = Différence entre les deux angles
// the if = Normaliser l'angle entre -π et π
// return = Convertir en degrés
double calculate_angle_opponent(double dx1, double dy1, double dx2, double dy2)
{
	double angle1;
	double angle2;
	double result;

	angle1 = atan2(dy1, dx1);
	angle2 = atan2(dy2, dx2);
	result = angle2 - angle1;
    if (result > M_PI)
		result -= 2 * M_PI;
	if (result < -M_PI)
		result += 2 * M_PI;
    return result * (180.0 / M_PI);
}

// angle = Calcul de l'angle entre les deux vecteurs
void	draw_opponent(t_game *game, t_player *opponent, t_player *player, int begin)
{
	t_ray_tex	ray_tex;
	t_sprite	*sprite;
	double		angle;

	angle = calculate_angle_opponent(opponent->dir_x, opponent->dir_y,
		opponent->pos_x - player->pos_x, opponent->pos_y - player->pos_y);
	if (angle > -45.0 && angle <= 45.0)
		opponent->sprite->index = 6;
	else if (angle > 45.0 && angle <= 135.0)
		opponent->sprite->index = 4;
	else if (angle > 135.0 || angle <= -135.0)
		opponent->sprite->index = 0;
	else
		opponent->sprite->index = 2;
	sprite = opponent->sprite;
	ray_tex.tex = &sprite->s_tex[sprite->index];
	draw_sprite_part_one(game, &ray_tex, sprite, player);
	draw_sprite_part_two(game, &ray_tex, ray_tex.tex, begin);
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

void	detection(t_game *game, t_enemie *enemie)
{
	if (enemie->sprite->sprite_x - game->player->pos_x <= 1
		&& enemie->sprite->sprite_x - game->player->pos_x >= -1)
	{
		if (enemie->sprite->sprite_y - game->player->pos_y <= 1
			&& enemie->sprite->sprite_y - game->player->pos_y >= -1)
		{
			printf("CHASE_ON\n");
			enemie->chase_status = 1;
		}
	}
	else if (game->gamemode == 2)
	{
		if (enemie->sprite->sprite_x - game->player_two->pos_x <= 1
			&& enemie->sprite->sprite_x - game->player_two->pos_x >= -1)
		{
			if (enemie->sprite->sprite_y - game->player_two->pos_y <= 1
				&& enemie->sprite->sprite_y - game->player_two->pos_y >= -1)
			{
				printf("CHASE_ON\n");
				enemie->chase_status = 2;
			}
		}
	}
}

void	move_enemies(t_game *game, t_enemie *enemie)
{
	int	temp_y;
	int	temp_x;

	temp_x = (int)enemie->sprite->sprite_x;
	temp_y = (int)enemie->sprite->sprite_y;
	if (enemie->chase_status == 1)
		chase(game, enemie, game->player);
	else if (enemie->chase_status == 2)
		chase(game, enemie, game->player_two);
	else
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
		else if (enemie->move_state == 3)
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
	if ((enemie->sprite->sprite_x - game->player->pos_x <= 0.1
		&& enemie->sprite->sprite_x - game->player->pos_x >= -0.1)
		&& (enemie->sprite->sprite_y - game->player->pos_y <= 0.1
		&& enemie->sprite->sprite_y - game->player->pos_y >= -0.1)) // a ameliorer
	{
		printf("game over\n");
		close_game(game, NULL);
	}
	else if (game->gamemode == 2)
	{
		if ((enemie->sprite->sprite_x - game->player_two->pos_x <= 0.1
		&& enemie->sprite->sprite_x - game->player_two->pos_x >= -0.1)
		&& (enemie->sprite->sprite_y - game->player_two->pos_y <= 0.1
		&& enemie->sprite->sprite_y - game->player_two->pos_y >= -0.1)) // a ameliorer
	{
		printf("game over\n");
		close_game(game, NULL);
	}
	}
}
