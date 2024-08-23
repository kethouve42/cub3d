/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sound_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kethouve <kethouve@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 16:12:13 by acasanov          #+#    #+#             */
/*   Updated: 2024/08/23 15:46:07 by kethouve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

unsigned long	hashstr(const char *str)
{
	unsigned long	hash;
	int				c;

	hash = 5381;
	c = *str++;
	while ((c))
	{
		hash = ((hash << 5) + hash) + c;
		c = *str++;
	}
	return (hash);
}

char	*is_attenued(char *base, int attenued)
{
	if (attenued)
		base = "paplay --volume=30000 sound/";
	else
		base = "paplay --volume=40000 sound/";
	return (base);
}

/* Play the .ogg file in parameter (name without path or extention) */
void	playsound(char *file, int wait, int stop, int attenued)
{
	char	*base;
	char	tmp[256];
	int		result;

	base = NULL;
	base = is_attenued(base, attenued);
	memset(tmp, 0, 256);
	memcpy(tmp, base, strlen(base));
	if (stop)
		result = system("pkill -f paplay");
	if (hashstr(file) == 2784)
		return ;
	memcpy(&tmp[strlen(base)], file, strlen(file));
	if (!wait)
		base = ".ogg &";
	else
		base = ".ogg";
	memcpy(&tmp[strlen(tmp)], base, strlen(base));
	result = system(tmp);
	if (result != 0)
		perror("");
}
