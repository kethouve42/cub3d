/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enemies.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kethouve <kethouve@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 15:26:08 by kethouve          #+#    #+#             */
/*   Updated: 2024/08/01 16:35:47 by kethouve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	add_enemies(t_game *game)
{
	game->graphics->sprites[game->graphics->sprite_count] = game->enemies.sprite;
	game->graphics->sprite_count++;
}