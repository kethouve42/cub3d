/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acasanov <acasanov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 16:46:14 by acasanov          #+#    #+#             */
/*   Updated: 2024/08/14 17:39:01 by acasanov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/* Get map dimensions*/
void	get_map_dimensions(t_game *game, int file_size, char **map)
{
	int	y;

	game->map_height = file_size - game->line_map;
	y = 0;
	while (y < game->map_height)
	{
		if (ft_strlen(map[y]) - 1 > game->map_length)
		{
			if (y == game->map_height)
				game->map_length = ft_strlen(map[y]);
			else
				game->map_length = ft_strlen(map[y]) - 1;
		}
		y++;
	}
}

/* Check if the map is cut by an empty or space line */
void	check_map_empty_line(t_game *game, char **map)
{
	int	y;
	int	check;

	y = 0;
	check = 1;
	while (y < game->map_height)
	{
		if (ft_line_empty(map[y]) == 1)
		{
			if (check == 0)
				close_game(game, "Empty line in map");
			check = 1;
		}
		else
			check = 0;
		y++;
	}
}

/* Get player start position and rotation */
void	get_player_start(t_game *game, char **map, int x, int y)
{
	t_player *player;

	player = game->player;

	if (game->player->player_start_rot != 0 && game->gamemode == 1)
		close_game(game, "Two or more player found");
	else if (game->gamemode == 2 && game->player->player_start_rot != 0 && game->player_two->player_start_rot == 0)
		player = game->player_two;
	else if (game->gamemode == 2 && game->player->player_start_rot != 0)
		close_game(game, "There is no two players");
	player->pos_x = y + 0.5;
	player->pos_y = x + 0.5;
	if (map[y][x] == 'N')
		player->player_start_rot = 1;
	else if (map[y][x] == 'E')
		player->player_start_rot = 2;
	else if (map[y][x] == 'S')
		player->player_start_rot = 3;
	else if (map[y][x] == 'W')
		player->player_start_rot = 4;
	map[y][x] = '0';
}

/* Check all characters on the map */
void	explore_map_value(t_game *game, char **map, int x, int y)
{
	while (map[y][x])
	{
		if (is_valid_char(map[y][x]) == 1 || map[y][x] == ' '
			|| map[y][x] == '\n')
		{
			if (is_into_str(map[y][x], "0NSEWDBPG"))
			{
				if (is_valid_coord(game, map, x, y) == 1)
					close_game(game, NULL);
				if (is_into_str(map[y][x], "NSWE"))
					get_player_start(game, map, x, y);
				if (map[y][x] == 'B' || map[y][x] == 'P')
					get_sprite(game, map, x, y);
				if (map[y][x] == 'G')
					get_enemie(game, map, x, y);
			}
		}
		else
		{
			printf("error: wrong char at %d:%d (%c found)\n", x, y, map[y][x]);
			close_game(game, NULL);
		}
		x++;
	}
	y++;
}

/* Retrieve the map and check its validity */
void	check_map(t_game *game, char *map_path, int file_size)
{
	int		y;

	while (game->cubfile[game->line_map]
		&& ft_line_empty(game->cubfile[game->line_map]) == 0)
		game->line_map++;
	if (game->cubfile[game->line_map] == NULL)
		close_game(game, "No maps found");
	game->map = copy_map(map_path, game, file_size
			- game->line_map, game->line_map);
	get_map_dimensions(game, file_size, game->map);
	check_how_many_sprites(game);
	check_map_empty_line(game, game->map);
	y = 0;
	while (y < game->map_height)
	{
		explore_map_value(game, game->map, 0, y);
		y++;
	}
	set_player_rot(game->player);
	if (game->gamemode == 2 && game->player_two->player_start_rot != 0)
		set_player_rot(game->player_two);
	else if (game->gamemode == 2)
		close_game(game, "No second player");
	if (game->player->player_start_rot == 0)
		close_game(game, "error : no player found");
}
