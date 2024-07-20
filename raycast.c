/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acasanov <acasanov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 14:34:37 by acasanov          #+#    #+#             */
/*   Updated: 2024/07/20 16:48:05 by acasanov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	convert_rgb_to_int(int r, int g, int b)
{
	return ((r << 16) | (g << 8) | b);
}

void	draw_skyground(t_game *game)
{
	int	ground;
	int	sky;
	int	x;
	int	y;

	ground = convert_rgb_to_int(game->graphics->color_ground[0],
			game->graphics->color_ground[1], game->graphics->color_ground[2]);
	sky = convert_rgb_to_int(game->graphics->color_sky[0],
			game->graphics->color_sky[1], game->graphics->color_sky[2]);
	y = 0;
	while (y < game->graphics->screen_height)
	{
		x = 0;
		while (x < game->graphics->screen_lenght)
		{
			if (y > game->graphics->screen_height / 2)
				my_mlx_pixel_put(game->img, y, x, ground);
			else
				my_mlx_pixel_put(game->img, y, x, sky);
			x++;
		}
		y++;
	}
}

void	draw_textured_wall(t_game *game, int x, int draw_start, int draw_end, double wall_x, int side, int line_height, int map_side) // A modfier au decoupage de raycast
{
	unsigned int	color;
	t_img			*tex;
	int				tex_x;
	int				tex_y;
	int				y;
	int				d;

	if (side == 1)
	{
		if (map_side == 1)
			tex = &game->graphics->text_w; //redbrick
		else
			tex = &game->graphics->text_e; //mossy
	}
	else
	{
		if (map_side == 1)
			tex = &game->graphics->text_n; //wood
		else
			tex = &game->graphics->text_s; //stone
	}
	// Select where in the x-axis in texture
	tex_x = (int)(wall_x * (double)(tex->width));
	if (side == 1 && map_side == 1)
		tex_x = tex->width - tex_x - 1;
	if (side == 0 && map_side == 2)
		tex_x = tex->width - tex_x - 1;
	y = draw_start;
	while (y < draw_end)
	{
		d = y * 256 - (game->graphics->screen_height / 2)
			* 256 + line_height * 128;
		tex_y = ((d * tex->height) / line_height) / 256;
		if (tex_x >= 0 && tex_x < tex->width && tex_y >= 0
			&& tex_y < tex->height)
			color = tex->data[tex_y * tex->width + tex_x];
		my_mlx_pixel_put(game->img, y, x, color);
		y++;
	}
}

void	raycast(t_game *game)
{
	int x;

	// Pour chaque colonne X de pixel de la fenetre...
	x = 0;
	while (x < (game->graphics->screen_lenght))
	{
		// Calcul le rayon (position et direction X et Y)
		double camera_x = 2 * x / (double)game->graphics->screen_lenght - 1; // position du rayon sur le plan caméra
		double ray_dir_x = game->player->dir_x + game->player->plane_x * camera_x;
		double ray_dir_y = game->player->dir_y + game->player->plane_y * camera_x;

		// Quelle case de la carte le joueur occupe
		int map_x = (int)game->player->pos_x;
		int map_y = (int)game->player->pos_y;

		//  =========================== DDA , faut pas chercher a comprendre pk =============================
		// Longueur du rayon de la position actuelle au prochain x ou y
		double side_dist_x;
		double side_dist_y;

		// Longueur du rayon d'un x ou y à l'autre
		double delta_dist_x = fabs(1 / ray_dir_x);
		double delta_dist_y = fabs(1 / ray_dir_y);
		double perp_wall_dist;

		// Direction à prendre en x et y (1 ou -1)
		int step_x;
		int step_y;

		int hit = 0; // A-t-on touché un mur ?
		int side; // Était-ce un mur vertical ou horizontal ?
		
		// Calculer la distance initiale aux côtés
		if (ray_dir_x < 0) {
			step_x = -1;
			side_dist_x = (game->player->pos_x - map_x) * delta_dist_x;
		} else {
			step_x = 1;
			side_dist_x = (map_x + 1.0 - game->player->pos_x) * delta_dist_x;
		}
		if (ray_dir_y < 0) {
			step_y = -1;
			side_dist_y = (game->player->pos_y - map_y) * delta_dist_y;
		} else {
			step_y = 1;
			side_dist_y = (map_y + 1.0 - game->player->pos_y) * delta_dist_y;
		}
		
		// DDA (Digital Differential Analysis)
		while (hit == 0)
		{
			// Aller au prochain carré
			if (side_dist_x < side_dist_y) {
				side_dist_x += delta_dist_x;
				map_x += step_x;
				side = 0;
			} else {
				side_dist_y += delta_dist_y;
				map_y += step_y;
				side = 1;
			}
			// Vérifier si un mur a été touché
			if (game->map[map_x][map_y] != '0')
				hit = 1;
		}

		// Calculer le rendu en cas d'inclinaison du plan camera vis-a-vis du mur
		if (side == 0) perp_wall_dist = (map_x - game->player->pos_x + (1 - step_x) / 2) / ray_dir_x;
		else          perp_wall_dist = (map_y - game->player->pos_y + (1 - step_y) / 2) / ray_dir_y;

		// Calculer la hauteur de ligne pour le dessin
		int line_height = (int)(game->graphics->screen_height / perp_wall_dist);

		// Calculer les valeurs de début et de fin de dessin
		int draw_start = -line_height / 2 + game->graphics->screen_height / 2;
		if (draw_start < 0) draw_start = 0;
		int draw_end = line_height / 2 + game->graphics->screen_height / 2;
		if (draw_end >= game->graphics->screen_height) draw_end = game->graphics->screen_height - 1;

		// Choisir la texture basée sur le côté et le mur touché
        int tex_num = game->map[map_x][map_y] - 49; // -49 car c'est des char qu'on convertit en int, donc -48 (et -1 pour que text1 = la 1ere texture)
        double wall_x; // position exacte où le mur a été touché
        if (side == 0) wall_x = game->player->pos_y + perp_wall_dist * ray_dir_y;
        else           wall_x = game->player->pos_x + perp_wall_dist * ray_dir_x;
        wall_x -= floor((wall_x));

		int map_side;
		if (side == 0)
		{
			if (map_x < game->player->pos_x)
				map_side = 1; // nord
			else
				map_side = 2; // sud
		}
		else
		{
			if (map_y < game->player->pos_y)
				map_side = 1; // Ouest
			else
				map_side = 2; // Est
		}
        // Dessiner la ligne texturée pour le mur
        draw_textured_wall(game, x, draw_start, draw_end, wall_x, side, line_height, map_side);
		x++;
	}
}
