#include "types.h"
#include "math.h"
#include "raycast.h"
#include <stdio.h>

void	open_door(t_game *game, int dir)
{
    t_map		*map = game->data->map;
	int			check_tile;
	int			pos;
	double	move_x = sin((game->data->yaw) * M_PI / 180) * 0.5;
	double	move_y = -cos((game->data->yaw) * M_PI / 180) * 0.5;
	// Calcul de la nouvelle position potentielle
	double new_x = game->data->player.x + (move_x * dir) + 0.5;
	double new_y = game->data->player.y + (move_y * dir) + 0.5;

	pos = (int)new_y * map->width + (int)new_x;
	check_tile = map->tiles[pos];
	printf("check_tile: %d\n", check_tile);
	if (check_tile == D)
		animate(game, pos, 0);
}
