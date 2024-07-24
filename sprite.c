/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acasanov <acasanov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 22:00:50 by kethouve          #+#    #+#             */
/*   Updated: 2024/07/24 19:45:35 by acasanov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void    get_sprite(t_game *game, char **map, int x, int y)
{
    t_sprite sprite;
    
    if (map[y][x] == 'B')
        sprite.s_tex = game->graphics->s_barrel;
    else if (map[y][x] == 'P')
        sprite.s_tex = game->graphics->s_pillar;
    sprite.x = y + 0.5;
    sprite.y = x + 0.5;
    sprite.size = 16;

    game->graphics->sprites[game->graphics->sprite_count] = sprite;
    game->graphics->sprite_count++;
}

void	sprite_init(t_game *game)
{
	//game->sprite = malloc(sizeof(t_sprite));
	//game->sprite->size = 16;
	//game->sprite->x = 4.5;
	//game->sprite->y = 4.5;
	//game->sprite->s_tex.img = NULL;
	game->z_buffer = (double *)malloc(sizeof(double) * (24 * 64));
	init_sprite(game);
}

void	init_sprite(t_game *game)
{
	char *path;
	path = ft_strdup("texture/pillar.xpm\n"); // a replacer par le parsing de la map
	load_texture(game, &game->graphics->s_pillar, path);

    path = ft_strdup("texture/barrel.xpm\n"); // a replacer par le parsing de la map
	load_texture(game, &game->graphics->s_barrel, path);

	path = ft_strdup("texture/door.xpm\n"); // a replacer par le parsing de la map
	load_texture(game, &game->graphics->tex_door, path);
}

void    draw_sprite(t_game *game, t_sprite *sprite)
{
	t_img	*tex;

	tex = &sprite->s_tex;
	/*calcul la position du sprite par rapport au joueur*/
    double spriteX = sprite->x - game->player->pos_x;
    double spriteY = sprite->y - game->player->pos_y;

	/*transforme les coordonnées du sprite par rapport a la carte en données par rapport a la caméra*/
    double invDet = 1.0 / (game->player->plane_x * game->player->dir_y - game->player->dir_x * game->player->plane_y);
    
	/*coordonnées du sprite par rapport a la caméra*/
	double transformX = invDet * (game->player->dir_y * spriteX - game->player->dir_x * spriteY);
    double transformY = invDet * (-game->player->plane_y * spriteX + game->player->plane_x * spriteY);

	/*calcul de la coordonnée x sur l'ecran*/
    int spriteScreenX = (int)((24 * 64 / 2) * (1 + transformX / transformY));

	/*calcul la hauteur et la largeur du sprite ainsi que le début de son dessin et sa fin*/
    int spriteHeight = abs((int)(11 * 64 / transformY)) / 1;
    int drawStartY = -spriteHeight / 2 + 11 * 64 / 2;
    if (drawStartY < 0) drawStartY = 0;
    int drawEndY = spriteHeight / 2 + 11 * 64 / 2;
    if (drawEndY >= 11 * 64) drawEndY = 11 * 64 - 1;

    int spriteWidth = abs((int)(11 * 64 / transformY)) / 1;
    int drawStartX = -spriteWidth / 2 + spriteScreenX;
    if (drawStartX < 0) drawStartX = 0;
    int drawEndX = spriteWidth / 2 + spriteScreenX;
    if (drawEndX >= 24 * 64) drawEndX = 24 * 64 - 1;

	/*dessin du sprite*/
    for (int stripe = drawStartX; stripe < drawEndX; stripe++) //pour chaque ligne de pixel vertical
	{
        int texX = (int)(256 * (stripe - (-spriteWidth / 2 + spriteScreenX)) * tex->width / spriteWidth) / 256;
        if (transformY > 0 && stripe > 0 && stripe < 24 * 64 && transformY < game->z_buffer[stripe]) {
            for (int y = drawStartY; y < drawEndY; y++) // pour chaque pixel sur cette ligne
			{
                int d = (y) * 256 - 11 * 64 * 128 + spriteHeight * 128;
                int texY = ((d * tex->height) / spriteHeight) / 256;
                unsigned int color = tex->data[texY * tex->width + texX];
                if ((color & 0x00FFFFFF) != 0) //check si le sprite est transparent
				{
                    my_mlx_pixel_put(game->img, y, stripe, color);
                }
            }
        }
    }
}
