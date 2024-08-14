/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acasanov <acasanov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 14:34:30 by acasanov          #+#    #+#             */
/*   Updated: 2024/08/14 19:57:35 by acasanov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <X11/Xlib.h>
# include <X11/Xutil.h>
# include <unistd.h>
# include <stdlib.h>
# include "../minilibx-linux/mlx.h"
# include <stdio.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <math.h>
# include <sys/time.h>
# include <string.h>

# define ROT_SPEED 0.01
# define MOVE_SPEED 0.04
# define HITBOX_SIZE 2
# define SPRITE_UPDATE 500

typedef struct s_img {
	void	*img;
	char	*addr;
	int		*data;
	int		width;
	int		height;
	int		size_l;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_img;

typedef struct s_player
{
	int		player_start_rot;
	double	pos_x;
	double	pos_y;
	double	dir_x;
	double	dir_y;
	double	plane_x;
	double	plane_y;
}			t_player;

typedef struct s_key
{
	int	forward;
	int	back;
	int	left;
	int	right;
	int	rotate_left;
	int	rotate_right;
	int	last_x;
}	t_key;

typedef struct s_raycast
{
	int				x;
	double			camera_x;
	double			ray_dir_x;
	double			ray_dir_y;
	int				map_x;
	int				map_y;
	double			side_dist_x;
	double			side_dist_y;
	double			delta_dist_x;
	double			delta_dist_y;
	double			perp_wall_dist;
	int				step_x;
	int				step_y;
	int				hit;
	int				side;
	int				line_height;
	int				draw_start;
	int				draw_end;
	int				tex_num;
	double			wall_x;
	int				map_side;
	unsigned int	color;
	t_img			*tex;
	int				tex_x;
	int				tex_y;
	int				y;
	int				d;
}		t_raycast;

typedef struct s_ray_tex
{
	double			sprite_x;
	double			sprite_y;
	double			inv_det;
	double			transform_x;
	double			transform_y;
	int				sprite_screen_x;
	int				sprite_height;
	int				draw_start_y;
	int				draw_end_y;
	int				sprite_width;
	int				draw_start_x;
	int				draw_end_x;
	int				stripe;
	int				tex_x;
	int				y;
	int				d;
	int				tex_y;
	unsigned int	color;
}			t_ray_tex;

typedef struct s_texture
{
	int		index;
	int		nb;
	t_img	*tex;
}			t_texture;

typedef struct s_sprite
{
	int		index;
	int		nb;
	double	x;
	double	y;
	double	sprite_x;
	double	sprite_y;
	t_img	*s_tex;
	int		size;
}			t_sprite;

typedef struct s_enemies
{
	int			hp;
	int			chase_status;
	int			move_state;
	int			move;
	int			n_move;
	t_sprite	*sprite;
}			t_enemie;

typedef struct s_graphics
{
	t_texture	tex_n;
	t_texture	tex_s;
	t_texture	tex_e;
	t_texture	tex_w;
	char		*tmp_path;
	t_img		tex_door;
	t_img		tex_door2;
	t_img		s_pillar;
	t_img		s_barrel;
	t_img		s_enemi_one;
	t_img		s_enemi_two;
	t_img		s_enemi_dead;
	t_sprite	**sprites;
	int			sprite_count;
	int			color_sky[3];
	int			color_ground[3];
	int			screen_height;
	int			screen_lenght;
}			t_graphics;

typedef struct s_game
{
	void		*mlx;
	void		*mlx_win;
	char		**cubfile;
	int			line_map;
	int			gamemode;
	char		**map;
	int			map_height;
	int			map_length;
	t_key		*key;
	t_key		*key2;
	t_img		*img;
	t_graphics	*graphics;
	t_player	*player;
	t_player	*player_two;
	t_enemie	**enemies;
	int			enemies_count;
	double		*z_buffer;
	int			start_time;
	int			last_time_update;
	int			last_ennemi_time_update;
}				t_game;

typedef struct s_map
{
	int	dx;
	int	dy;
	int	sx;
	int	sy;
	int	err;
	int	e2;
	int	color;
	int	x0;
	int	y0;
}				t_map;

/* ====================== MINIMAP ==================== */
int		minimap(t_game *game);

/* ======================= TIME ====================== */
int		get_current_time(void);
void	update_all_sprites_index(t_game *game);

/* ====================== SOUND ===================== */
void	playsound(char *file, int wait, int stop, int attenued);

/* ===================== RAYCAST ==================== */
void	raycast(t_game *game, t_player *player, int begin, int end);
void	raycast_part_one(t_game *game, t_raycast *raycast, t_player *player);
void	raycast_part_two(t_game *game, t_raycast *raycast, t_player *player);
void	raycast_part_three(t_game *game, t_raycast *raycast, t_player *player);
void	raycast_part_four(t_game *game, t_raycast *raycast, t_player *player);
void	raycast_part_five(t_game *game, t_raycast *raycast, t_player *player);
void	raycast_part_six(t_game *game, t_raycast *raycast);
void	raycast_part_three_door(t_game *game, t_raycast *raycast);
void	raycast_part_five_door(t_game *game, t_raycast *raycast);
void	draw_sprite_part_one(t_game *game, t_ray_tex *ray_tex, t_sprite *sprite, t_player *player);
void	draw_sprite_part_two(t_game *game, t_ray_tex *ray_tex, t_img *tex, int begin);

/* ===================== GRAPHICS ==================== */
void	draw_skyground(t_game *game);
void	my_mlx_pixel_put(t_img *img, int y, int x, int color);
void	sprite_init(t_game *game);
void	draw_sprite(t_game *game, t_player *player, int begin);
void	check_how_many_sprites(t_game *game);
void	get_sprite(t_game *game, char **map, int x, int y);
void	sprite_sort(t_graphics *graphics, t_game *game, t_player *player);
t_img	*set_test_texture_two(t_game *game, int *check, int check_tmp);

/* ===================== PARSING ==================== */
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
void	set_player_rot(t_player *player);
void	check_how_many_texture(t_game *game);

/* ===================== PLAYER ==================== */
int		player(t_game *game);
int		key_press(int keycode, t_game *game);
int		key_release(int keycode, t_game *game);
int		mouse(int x, int y, t_game *game);
void	player_forward_back(t_game *game, double speed, int temp_x, int temp_y, t_player *player, t_key *key);
void	player_right_left(t_game *game, double speed, int temp_x, int temp_y, t_player *player, t_key *key);
void	player_rotation(t_game *game, double old_dir_x, double old_plane_x, t_player *player, t_key *key);
void	open_door(t_game *game, int y, int x, char **map);

/* ============== CLOSE ============== */
int		close_game(t_game *game, char *error_msg);
void	free_image(t_game *game, t_img *img);
void	free_tab(char **tab);
int		red_cross(t_game *game);

/* ===================== UTILS ==================== */
char	*get_next_line(int fd);
size_t	ft_strlen(char *s);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
int		ft_atoi(const char *str);
void	*ft_calloc(size_t count, size_t size);
int		ft_isnum(char c);
int		ft_isalnum(char c);
int		ft_line_empty(char *s);
char	*skip_empty(char *str);
int		get_lines(t_game *game, char *map_path);
char	**copy_map(char *map_path, t_game *game, int file_size, int override);
char	*ft_strdup(const char *s1);
int		is_into_str(char c, char *str);
void	init_map_line(t_map	*map, t_player	*player, int x1, int y1);

/* ===================== DEBUG ==================== */
void	display_map(char **map);
void	display_key_input(t_game *game);
void	display_player_info(t_player *player);
void	display_texture_info(t_img *texture);
void	display_color(t_game *game);

/*======================== ENNEMIES ========================*/
void	draw_ennemies(t_game *game, t_sprite *ennemie);
int	ray_intersects_wall(t_game *game, t_sprite *enemie, double ray_dir_x, double ray_dir_y);
double	calculate_distance(double x1, double y1, double x2, double y2);
double	calculate_angle(double dir_x1, double dir_y1, double dir_x2,
			double dir_y2);
int		check_shot(t_game *game, t_sprite *enemies);
void	shoot(t_game *game);
void	draw_cursor(t_game *game);
void	get_enemie(t_game *game, char **map, int x, int y);
void	enemies_sort(t_enemie **enemies, t_game *game, t_player *player);
void	move_enemies(t_game *game, t_enemie *enemie);

#endif
