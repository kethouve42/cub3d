/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acasanov <acasanov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 14:34:37 by acasanov          #+#    #+#             */
/*   Updated: 2024/07/18 19:55:36 by acasanov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "cub3d.h"

int convert_rgb_to_int(int r, int g, int b)
{
    return (r << 16) | (g << 8) | b;
}

void draw_skyground(t_game *game)
{
	int screenWidth = 24 * 64;
	int screenHeight = 11 * 64;

	int ground;
	int sky;

	ground = convert_rgb_to_int(game->graphics->color_ground[0], game->graphics->color_ground[1], game->graphics->color_ground[2]);
	sky = convert_rgb_to_int(game->graphics->color_sky[0], game->graphics->color_sky[1], game->graphics->color_sky[2]);

	int	x = 0;
	int	y = 0;
	while (y < screenHeight)
	{
		x = 0;
		while (x < screenWidth)
		{
			if (y > screenHeight / 2)
				my_mlx_pixel_put(game->img, y, x, ground);
			else
				my_mlx_pixel_put(game->img, y, x, sky);
			x++;
		}
		y++;
	}
}

void    draw_textured_wall(t_game *game, int x, int drawStart, int drawEnd, double wallX, int side, int lineHeight, int rayDirX, int rayDirY, int mapSide)
{
	t_img   *tex;
	if(side == 1)
	{
		if (mapSide == 1)
			tex = &game->graphics->textW; //redbrick
		else
			tex = &game->graphics->textE; //mossy
	}
	else
	{
		if (mapSide == 1)
			tex = &game->graphics->textN; //wood
		else
			tex = &game->graphics->textS; //stone
	}
	
	// Select where in the x-axis in texture
    int     texX = (int)(wallX * (double)(tex->width));
	if(side == 1 && mapSide == 1)
		texX = tex->width - texX - 1;
	if(side == 0 && mapSide == 2)
		texX = tex->width - texX - 1;

	//printf("textX : %d -> %d        rayX : %d  rayY : %d, side : %d\n", texX, (int)(wallX * (double)(tex->width)), rayDirX, rayDirY, side);

	//printf("tex w %d, tex h %d\n", tex->width, tex->height);

    for (int y = drawStart; y < drawEnd; y++)
    {
		int d = y * 256 - (11 * 32) * 256 + lineHeight * 128;     // <======== 11*32 c'est la MOITIE de la taille de l'ecran, a remplacer par screenHeight
        int texY = ((d * tex->height) / lineHeight) / 256;

		unsigned int color;
		if (texX >= 0 && texX < tex->width && texY >= 0 && texY < tex->height)
            color = tex->data[texY * tex->width + texX];
		
		my_mlx_pixel_put(game->img, y, x, color);
    }
}

void raycast(t_game *game)
{
	// Dimensions ecran
	int screenWidth = 24 * 64;
	int screenHeight = 11 * 64;

	int x = 0;

	// Pour chaque colonne X de pixel de la fenetre...
	while (x < (screenWidth))
	{
		// Calcul le rayon (position et direction X et Y)
		double cameraX = 2 * x / (double)screenWidth - 1; // position du rayon sur le plan caméra
		double rayDirX = game->player->dirX + game->player->planeX * cameraX;
		double rayDirY = game->player->dirY + game->player->planeY * cameraX;

		// Quelle case de la carte le joueur occupe
		int mapX = (int)game->player->posX;
		int mapY = (int)game->player->posY;

		//  =========================== DDA , faut pas chercher a comprendre pk =============================
		// Longueur du rayon de la position actuelle au prochain x ou y
		double sideDistX;
		double sideDistY;

		// Longueur du rayon d'un x ou y à l'autre
		double deltaDistX = fabs(1 / rayDirX);
		double deltaDistY = fabs(1 / rayDirY);
		double perpWallDist;

		// Direction à prendre en x et y (1 ou -1)
		int stepX;
		int stepY;

		int hit = 0; // A-t-on touché un mur ?
		int side; // Était-ce un mur vertical ou horizontal ?
		
		// Calculer la distance initiale aux côtés
		if(rayDirX < 0) {
			stepX = -1;
			sideDistX = (game->player->posX - mapX) * deltaDistX;
		} else {
			stepX = 1;
			sideDistX = (mapX + 1.0 - game->player->posX) * deltaDistX;
		}
		if(rayDirY < 0) {
			stepY = -1;
			sideDistY = (game->player->posY - mapY) * deltaDistY;
		} else {
			stepY = 1;
			sideDistY = (mapY + 1.0 - game->player->posY) * deltaDistY;
		}
		
		// DDA (Digital Differential Analysis)
		while(hit == 0) // ================> Ici, mettre une limite max pour avoir une render distance
		{
			// Aller au prochain carré
			if(sideDistX < sideDistY) {
				sideDistX += deltaDistX;
				mapX += stepX;
				side = 0;
			} else {
				sideDistY += deltaDistY;
				mapY += stepY;
				side = 1;
			}
			// Vérifier si un mur a été touché
			if(game->map[mapX][mapY] != '0')
				hit = 1;
		}

		// Calculer le rendu en cas d'inclinaison du plan camera vis-a-vis du mur
		if(side == 0) perpWallDist = (mapX - game->player->posX + (1 - stepX) / 2) / rayDirX;
		else          perpWallDist = (mapY - game->player->posY + (1 - stepY) / 2) / rayDirY;

		// Calculer la hauteur de ligne pour le dessin
		int lineHeight = (int)(screenHeight / perpWallDist);

		// Calculer les valeurs de début et de fin de dessin
		int drawStart = -lineHeight / 2 + screenHeight / 2;
		if(drawStart < 0) drawStart = 0;
		int drawEnd = lineHeight / 2 + screenHeight / 2;
		if(drawEnd >= screenHeight) drawEnd = screenHeight - 1;

		// Choisir la texture basée sur le côté et le mur touché
        int texNum = game->map[mapX][mapY] - 49; // -49 car c'est des char qu'on convertit en int, donc -48 (et -1 pour que text1 = la 1ere texture)
        double wallX; // position exacte où le mur a été touché
        if (side == 0) wallX = game->player->posY + perpWallDist * rayDirY;
        else           wallX = game->player->posX + perpWallDist * rayDirX;
        wallX -= floor((wallX));

		int mapSide;
		if(side == 0)
		{
			if(mapX < game->player->posX)
				mapSide = 1; // nord
			else
				mapSide = 2; // sud
		}
		else
		{
			if(mapY < game->player->posY)
				mapSide = 1; // Ouest
			else
				mapSide = 2; // Est
		}

        // Dessiner la ligne texturée pour le mur
        draw_textured_wall(game, x, drawStart, drawEnd, wallX, side, lineHeight, rayDirX, rayDirY, mapSide);
		
		x++;
	}
}
