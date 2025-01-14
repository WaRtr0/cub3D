#include "game.h"
#include "layer.h"

static inline void	center_offset_player_on_map(t_game *game)
{
	t_layer	*group;
	t_layer	*map;
	t_layer	*map_mask;

	group = layer_stack_get(game->layers, 2);
	map = layer_group_get(group, 0);
	map_mask = layer_group_get(group, 1);

	layer_set_offset(map,
		(map_mask->width >> 1) - (
			game->data->player.x * SCALE_2D) - (SCALE_2D >> 1),
		(map_mask->height >> 1) - (
			game->data->player.y * SCALE_2D) - (SCALE_2D >> 1)
		);
}

static inline void	move_along(t_game *game, int side,
	double new_x, double new_y)
{
	if (side == 0 && new_y < game->data->player.y + 0.5)
		game->data->player.y = new_y - 0.5;
	else if (side == 1 && new_x > game->data->player.x + 0.5)
		game->data->player.x = new_x - 0.5;
	else if (side == 2 && new_y > game->data->player.y + 0.5)
		game->data->player.y = new_y - 0.5;
	else if (side == 3 && new_x < game->data->player.x + 0.5)
		game->data->player.x = new_x - 0.5;
}

void	check_new(t_game *game, int check_tile, double new_x, double new_y)
{
	int					i;
	double				check_x;
	double				check_y;
	static const int	check_points[][2] = {{0, -1}, {1, 0}, {0, 1}, {-1, 0}};
	const t_map			*map = game->data->map;

	i = 0;
	while (i < 4)
	{
		check_x = new_x + (check_points[i][0] * HIT_BOX);
		check_y = new_y + (check_points[i][1] * HIT_BOX);
		if ((check_x >= 0) | (check_x < map->width)
			| (check_y >= 0) | (check_y < map->height))
		{
			check_tile = map->tiles[(int)check_y * map->width + (int)check_x];
			if (check_tile != W && check_tile != D)
				move_along(game, i, new_x, new_y);
		}
		i++;
	}
}

void	player_move(t_game *game, int dir)
{
	const t_map			*map = game->data->map;
	int					check_tile;
	double				new_x;
	double				new_y;

	new_x = game->data->player.x + (cos((game->data->yaw) * M_RAD)
			* (STEP + game->player_state.running * STEP) * dir) + 0.5;
	new_y = game->data->player.y + (sin((game->data->yaw) * M_RAD)
			* (STEP + game->player_state.running * STEP) * dir) + 0.5;
	check_tile = map->tiles[(int)new_y * map->width + (int)new_x];
	if (check_tile == W || check_tile == D)
		return ;
	check_new(game, check_tile, new_x, new_y);
	center_offset_player_on_map(game);
}
