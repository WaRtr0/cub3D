#include "types.h"
#include "math.h"
#include "raycast.h"
#include <stdio.h>


void	open_door(t_game *game, int dir)
{
    t_map		*map = game->data->map;
	int			check_tile;
	int			pos;
	double	move_x = cos((game->data->yaw) * M_PI / 180) * 1.5;
	double	move_y = sin((game->data->yaw) * M_PI / 180) * 1.5;
	double new_x = game->data->player.x + (move_x * dir) + 0.5;
	double new_y = game->data->player.y + (move_y * dir) + 0.5;

	pos = (int)new_y * map->width + (int)new_x;
	check_tile = map->tiles[pos];
	if (check_tile == D)
		animate(game, pos, 0);
	else
	{
		move_x = cos((game->data->yaw) * M_PI / 180) * 0.75;
		move_y = sin((game->data->yaw) * M_PI / 180) * 0.75;
		new_x = game->data->player.x + (move_x * dir) + 0.5;
		new_y = game->data->player.y + (move_y * dir) + 0.5;
		pos = (int)new_y * map->width + (int)new_x;
		check_tile = map->tiles[pos];
		if (check_tile == D)
			animate(game, pos, 0);
	}
}
