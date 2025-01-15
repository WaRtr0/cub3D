/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_parsing.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gladius <gladius@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 19:15:20 by garivo            #+#    #+#             */
/*   Updated: 2025/01/15 15:23:58 by gladius          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static t_map_tile	*convert_map(t_map_tile *tiles, t_parsing *map,
	size_t i, size_t offset)
{
	while (i + offset < (unsigned int)(map->height * (map->width + 1)))
	{
		if (map->map[i + offset] == 'N')
			tiles[i] = P;
		else if (map->map[i + offset] == 'S')
			tiles[i] = P;
		else if (map->map[i + offset] == 'E')
			tiles[i] = P;
		else if (map->map[i + offset] == 'W')
			tiles[i] = P;
		else if (map->map[i + offset] == '1')
			tiles[i] = W;
		else if (map->map[i + offset] == '0' || map->map[i + offset] == ' ')
			tiles[i] = E;
		else if (map->map[i + offset] == '\0' && i--)
			offset++;
		else if (map->map[i + offset] == 'D')
			tiles[i] = D;
		i++;
	}
	tiles[i] = '\0';
	return (tiles);
}

int	convert_parsing(t_game *game, t_parsing *map)
{
	t_map_tile	*tiles;

	game->data->map = malloc(sizeof(t_map));
	if (!game->data->map)
		return (0);
	game->data->player.x = map->player_x;
	game->data->player.y = map->player_y;
	game->data->yaw = map->player_dir * 90;
	game->data->map->tiles = NULL;
	game->data->map->height = map->height;
	game->data->map->width = map->width;
	tiles = malloc(sizeof(t_map_tile) * map->height * (map->width + 1));
	if (!tiles)
		return (0);
	game->data->map->tiles = convert_map(tiles, map, 0, 0);
	return (1);
}
