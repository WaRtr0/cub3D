#include "game.h"
#include "draw.h"
#include "layer.h"
#include "map.h"

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

// color => const //valgrind
static void	build_map(t_map *ms, t_game *game, t_layer *map)
{
	t_dvector2		pos;

	pos = (t_dvector2){0, 0};
	while (pos.y < ms->height)
	{
		pos.x = 0;
		while (pos.x < ms->width)
		{
			if (ms->tiles[(int)pos.y * ms->width + (int)pos.x] == W)
				draw_rect_fill(map, (t_vector2){pos.x * SCALE_2D,
					pos.y * SCALE_2D}, (t_vector2){(pos.x + 1) * SCALE_2D,
					(pos.y + 1) * SCALE_2D}, pixel_create(0, 0, 0, 255));
			else if (ms->tiles[(int)pos.y * ms->width + (int)pos.x] == P)
			{
				game->data->player.x = pos.x;
				game->data->player.y = pos.y;
			}
			draw_rect(map, (t_vector2){pos.x * SCALE_2D, pos.y * SCALE_2D},
				(t_vector2){(pos.x + 1) * SCALE_2D, (pos.y + 1) * SCALE_2D},
				pixel_create(0, 0, 0, 175));
			pos.x++;
		}
		pos.y++;
	}
}

void	map_init(t_map *map_struct, t_game *game)
{
	t_layer			*group;
	t_layer			*map;

	group = layer_group_create(((250 * MAP_SIZE_RATIO) / RATIO),
			((250 * MAP_SIZE_RATIO) / RATIO), 2);
	layer_stack_add(game->layers, group);
	map = layer_create(game->mlx, map_struct->width * SCALE_2D,
			map_struct->height * SCALE_2D, 0);
	layer_fill(map, pixel_create(125, 125, 125, 200));
	layer_group_add(group, map);
	layer_set_offset(group, MAP_OFFSET, MAP_OFFSET);
	map_draw_init(game, group, map_struct);
	build_map(map_struct, game, map);
	center_offset_player_on_map(game);
	layer_volatile_on(map);
	yaw_init(game);
	if ((OUTPUT_WIDTH / RATIO) < MIN_WIDTH
		|| (OUTPUT_HEIGHT / RATIO) < MIN_WIDTH)
		map->visible = false;
}
