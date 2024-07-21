/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acasanov <acasanov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 14:34:30 by acasanov          #+#    #+#             */
/*   Updated: 2024/07/21 17:21:34 by acasanov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <unistd.h>
# include <stdlib.h>
# include "./minilibx-linux/mlx.h"
# include <stdio.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <math.h>

# define ROT_SPEED 0.02
# define MOVE_SPEED 0.04
# define HITBOX_SIZE 2

typedef struct s_img {
	void	*img;
	char	*addr;
	int		*data; // add during texture
	int		width; // add during texture
	int		height; // add during texture
	int		size_l; // add during texture
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_img;

typedef struct s_player
{
	double	pos_x;
	double	pos_y;
	double	dir_x;
	double	dir_y;
	double	plane_x;
	double	plane_y;
	//int	size;
	//int	color;
}			t_player;

typedef struct s_key
{
	int	forward;
	int	back;
	int	left;
	int	right;
	int	rotate_left;
	int	rotate_right;
}	t_key;

typedef struct s_raycast
{
	int		x;
	double	camera_x;
	double	ray_dir_x;
	double	ray_dir_y;
	int		map_x;
	int		map_y;
	double	side_dist_x;
	double	side_dist_y;
	double	delta_dist_x;
	double	delta_dist_y;
	double	perp_wall_dist;
	int		step_x;
	int		step_y;
	int		hit;
	int		side;
	int		line_height;
	int		draw_start;
	int		draw_end;
	int		tex_num;
	double	wall_x;
	int		map_side;

}		t_raycast;

typedef struct s_graphics
{
	t_img	text_n;
	t_img	text_s;
	t_img	text_e;
	t_img	text_w;
	int		color_sky[3];
	int		color_ground[3];
	int		screen_height;
	int		screen_lenght;
}			t_graphics;

typedef struct s_game
{
	void		*mlx;
	void		*mlx_win;
	char		**cubfile;
	int			line_map;
	char		**map;
	int			map_height; // taille en case
	int			map_length; // taille en case
	int			player_start_rot;
	t_key		*key;
	t_img		*img;
	t_graphics	*graphics;
	t_player	*player;
}				t_game;

/* ============== FONCTIONS NON CLASSEES ==============*/
void	raycast(t_game *game);
void	draw_skyground(t_game *game);
void	my_mlx_pixel_put(t_img *img, int x, int y, int color);
char	*get_next_line(int fd);
int		close_game(t_game *game, char *error_msg);

/* ===================== PARSING ====================*/
void	map_analysis(t_game *game, char *map_path);
void	check_map(t_game *game, char *map_path, int file_size);
void	load_texture(t_game *game, t_img *texture, char *file_path);
int		convert_rgb_to_int(int r, int g, int b);
void	check_graphics(t_game *game);
void	parse_color(t_game *game, char *str, char c);
void	check_path(t_game *game, char *map_path, int file_size);
char	**copy_map(char *map_path, t_game *game, int file_size, int override);
int		is_valid_char(char c);
int		is_valid_coord(t_game *game, char **map, int x, int y);
void	set_player_rot(t_game *game);

/* ===================== PLAYER ====================*/
int		player(t_game *game);
int		key_press(int keycode, t_game *game);
int		key_release(int keycode, t_game *game);
void	player_rotation(t_game *game, double old_dir_x, double old_plane_x);
void	player_forward_back(t_game *game, double speed, int temp_x, int temp_y);
void	player_right_left(t_game *game, double speed, int temp_x, int temp_y);

/* ===================== UTILS ====================*/
size_t	ft_strlen(char *s);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
int		ft_atoi(const char *str);
void	*ft_calloc(size_t count, size_t size);
int		ft_isnum(char c);
int		ft_isalnum(char c);
int		ft_line_empty(char *s);
void	free_tab(char **tab);
char	*skip_empty(char *str);
int		get_lines(t_game *game, char *map_path);
char	**copy_map(char *map_path, t_game *game, int file_size, int override);

/* ===================== DEBUG ====================*/
void	display_map(char **map);
void	display_key_input(t_game *game);
void	display_player_info(t_game *game);
void	display_texture_info(t_img *texture);
void	display_color(t_game *game);

#endif
