/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enemies_ter.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acasanov <acasanov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 16:12:12 by acasanov          #+#    #+#             */
/*   Updated: 2024/08/21 16:12:40 by acasanov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	swap_enemies(t_enemie *a, t_enemie *b)
{
	t_enemie	temp;

	temp = *a;
	*a = *b;
	*b = temp;
}

double	calculate_angle_opponent(double dx1, double dy1, double dx2, double dy2)
{
	double	angle1;
	double	angle2;
	double	result;

	angle1 = atan2(dy1, dx1);
	angle2 = atan2(dy2, dx2);
	result = angle2 - angle1;
	if (result > M_PI)
		result -= 2 * M_PI;
	if (result < -M_PI)
		result += 2 * M_PI;
	return (result * (180.0 / M_PI));
}
