/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acasanov <acasanov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 15:14:54 by acasanov          #+#    #+#             */
/*   Updated: 2024/07/20 21:53:05 by acasanov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include "cub3d.h"

size_t	ft_strlen(char *s)
{
	size_t	i;

	if (!s)
		return (0);
	i = 0;
	while (s[i])
		i++;
	return (i);
}

char	*ft_strjoinfree(char *s1, char *s2)
{
	size_t	i;
	size_t	j;
	char	*str;

	str = (char *)malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!str)
		return (NULL);
	i = 0;
	j = 0;
	while (s1[i])
	{
		str[i] = s1[i];
		i++;
	}
	while (s2[j])
	{
		str[i + j] = s2[j];
		j++;
	}
	str[i + j] = 0;
	free (s1);
	return (str);
}

char	*ft_strdup(const char *s1)
{
	int		i;
	int		size;
	char	*dest;

	i = 0;
	size = 0;
	while (s1[size])
		size++;
	dest = (char *)malloc((size + 1) * sizeof(char));
	if (dest == NULL)
		return (NULL);
	while (s1[i])
	{
		dest[i] = s1[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

void	*ft_calloc(size_t count, size_t size)
{
	void	*ptr;

	ptr = (void *)malloc(count * size);
	if (!ptr)
		return (NULL);
	ft_bzero(ptr, count);
	return (ptr);
}

void	ft_bzero(void *s, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		*(char *)(s + i) = '\0';
		i++;
	}
}

/* ===================== DEBUG ====================*/
void	display_map(char **map)
{
	int	i;

	i = 0;
	printf("=== Map ===\n");
	while (map[i])
	{
		printf("%s", map[i]);
		i++;
	}
	printf("\n");
}

void	display_key_input(t_game *game)
{
	printf("\n== Key control ==\n    |%d|\n", game->key->forward);
	printf("|%d| |%d| |%d|", game->key->left, game->key->back,
		game->key->right);
	printf("     |%d||%d|\n", game->key->rotate_left,
		game->key->rotate_right);
}

void	display_player_info(t_game *game)
{
	printf("=== Player info ===\nPosition : [%f:%f]\n",
		game->player->pos_x, game->player->pos_y);
	printf("Rotation : [%f:%f]\n", game->player->dir_x,
		game->player->dir_y);
	printf("Plane    : [%f:%f]\n", game->player->plane_x,
		game->player->plane_y);
	printf("\n");
}

void	display_texture_info(t_img *texture)
{
	printf("=== Texture info ===\n");
	printf("Size : %dx%d\n", texture->width, texture->height);
	printf("addr: %s\ndata : %d\nsize_l : %d\n", texture->addr,
		*texture->data, texture->size_l);
	printf("bit per pixel : %dd\nline lenght : %d\nendian : %d\n",
		texture->bits_per_pixel, texture->line_length, texture->endian);
	printf("\n");
}

void	display_color(t_game *game)
{
	printf("=== Color background ===\n");
	printf("Sky color    : %d,%d,%d\n", game->graphics->color_sky[0],
		game->graphics->color_sky[1], game->graphics->color_sky[2]);
	printf("Ground color : %d,%d,%d\n",
		game->graphics->color_ground[0], game->graphics->color_ground[1],
		game->graphics->color_ground[2]);
	printf("\n");
}
