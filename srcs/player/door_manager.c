#include "types.h"
#include "math.h"
#include "raycast.h"
#include <stdio.h>

static int	hold_wall(int pos)
{
	static int	hold = -1;
	int			res;

	res = -1;
	if (pos != -1)
		hold = pos;
	else
	{
		res = hold;
		hold = -1;
	}
	return (res);
}

static int	check_hitbox_door(t_game *game, int pos, double new_x, double new_y)
{
	int					i;
	double				check_x;
	double				check_y;
	static const int	check_points[][2] = {{0, -1}, {1, 0}, {0, 1}, {-1, 0}};
	const t_map			*map = game->data->map;

	i = 0;
	while (i < 4)
	{
		check_x = new_x + (check_points[i][0] * DOOR_HIT_BOX);
		check_y = new_y + (check_points[i][1] * DOOR_HIT_BOX);
		if ((check_x >= 0) | (check_x < map->width)
			| (check_y >= 0) | (check_y < map->height))
		{
			pos = (int)check_y * map->width + (int)check_x;
			if (map->tiles[pos] == W)
				hold_wall(pos);
			if (map->tiles[pos] == D)
				return (pos);
		}
		i++;
	}
	return (hold_wall(-1));
}

int	ray_door(t_game *game, int dir, int i)
{
	int			pos;
	double		new_x;
	double		new_y;
	t_map		*map;

	map = game->data->map;
	while (i++ < 150)
	{
		new_x = game->data->player.x + (cos((game->data->yaw) * M_PI / 180)
				* DOOR_STEP * i * dir) + 0.5;
		new_y = game->data->player.y + (sin((game->data->yaw) * M_PI / 180)
				* DOOR_STEP * i * dir) + 0.5;
		pos = (int)new_y * map->width + (int)new_x;
		if (map->tiles[pos] == D)
			return (pos);
		pos = check_hitbox_door(game, 0, new_x, new_y);
		if (pos != -1)
		{
			if (map->tiles[pos] == D)
				return (pos);
			break ;
		}
	}
	return (-1);
}

void	open_door(t_game *game, int dir)
{
	int	pos;

	pos = ray_door(game, dir, 0);
	if (pos != -1)
		animate(game, pos, 0);
}
