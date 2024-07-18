/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acasanov <acasanov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 14:34:30 by acasanov          #+#    #+#             */
/*   Updated: 2024/07/18 17:12:37 by acasanov         ###   ########.fr       */
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

# define ROT_SPEED 0.03 // Vitesse de rotation
# define MOVE_SPEED 0.05 // Vitesse de rotation

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

typedef struct s_key
{
	int	forward;
	int back;
	int left;
	int right;
	int rotate_left;
	int rotate_right;
}				t_key;

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
	int			lineMap;
	char		**map;
	int			mapHeight;
	int			mapLength;
	int			playerStartRot;
	t_key		*key;
	t_img		*img;
	t_graphics	*graphics;
	t_player	*player;
}				t_game;

void raycast(t_game *game);
void draw_skyground(t_game *game);
void	my_mlx_pixel_put(t_img *img, int x, int y, int color);
char	*get_next_line(int fd);
int	map_analysis(t_game *game, char *map_path);
void    load_texture(t_game *game, t_img *texture, char *file_path);
int	close_game(t_game *game, char *error_msg);

/* ===================== UTILS ====================*/
int	ft_strncmp(const char *s1, const char *s2, size_t n);
size_t	ft_strlen(char *s);
int	ft_atoi(const char *str);
void	*ft_calloc(size_t count, size_t size);
int ft_isnum(char c);
int ft_isalnum(char c);
int ft_line_empty(char *s);
void	free_tab(char **tab);

/* ===================== DEBUG ====================*/
void	display_map(char **map);

#endif
