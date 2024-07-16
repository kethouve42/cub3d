/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acasanov <acasanov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 14:34:30 by acasanov          #+#    #+#             */
/*   Updated: 2024/07/16 19:57:36 by acasanov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D
# define CUB3D

# include <unistd.h>
# include <stdlib.h>
# include "./minilibx-linux/mlx.h"
# include <stdio.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <math.h>

# define ROT_SPEED 0.1 // Vitesse de rotation

typedef struct	s_img {
	void	*img;
	char	*addr;
	int         *data; // add texture
	int         width; // add texture
    int         height; // add texture
	int         size_l; // add texture
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_img;

typedef struct	s_player
{
	double	posX;
	double	posY;
	int	size;
	int	color;
	double	dirX;
	double	dirY;
	double	planeX;
	double	planeY;
}				t_player;

typedef struct s_graphics
{
	t_img		textN;
	t_img		textS;
	t_img		textE;
	t_img		textW;
	int			color_sky[3];
	int 		color_ground[3];
	int mapHeight;
	int mapLenght;
}				t_graphics;

typedef struct s_game
{
	void		*mlx;
	void		*mlx_win;
	char		**cubfile;
	char		**map;
	//int	screenHeight;
	//int screenWidth;
	t_img		img;
	t_graphics	*graphics;
	t_img		textures[4]; // Obselete
	t_player	*player;
	
}				t_game;

void raycast(t_game *game);
void draw_skyground(t_game *game);
void	my_mlx_pixel_put(t_img *img, int x, int y, int color);
char	*get_next_line(int fd);
int	map_analysis(t_game *game, char *map_path);
void    load_texture(t_game *game, t_img *texture, char *file_path);

/* ===================== UTILS ====================*/
int	ft_strncmp(const char *s1, const char *s2, size_t n);
size_t	ft_strlen(char *s);
int	ft_atoi(const char *str);
int ft_isnum(char c);

/* ===================== DEBUG ====================*/
void	display_map(char **map);

#endif
