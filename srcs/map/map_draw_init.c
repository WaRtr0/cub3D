#include "game.h"
#include "draw.h"
#include "layer.h"

static void	draw_all_circle(t_layer *circle_map, t_layer *map_mask)
{
	const unsigned int	half_map = MAP_SIZE >> 1;

	draw_circle_fill(map_mask, (t_vector2){half_map, half_map},
		half_map, pixel_create(0, 0, 0, 255));
	draw_circle(circle_map, (t_vector2){half_map, half_map},
		half_map - 5, pixel_create(255, 255, 0, 255));
	draw_circle(circle_map, (t_vector2){half_map, half_map},
		half_map - 4, pixel_create(200, 200, 0, 255));
	draw_circle(circle_map, (t_vector2){half_map, half_map},
		half_map - 3, pixel_create(150, 150, 0, 255));
	draw_circle(circle_map, (t_vector2){half_map, half_map},
		half_map - 2, pixel_create(150, 150, 0, 255));
	draw_circle(circle_map, (t_vector2){half_map, half_map},
		half_map - 1, pixel_create(100, 100, 0, 255));
	draw_circle(circle_map, (t_vector2){half_map, half_map},
		half_map - 0, pixel_create(50, 50, 0, 255));
}

static t_layer	*add_player(t_game *game)
{
	t_layer	*player;
	t_layer	*rotate;
	t_layer	*cursor;

	cursor = layer_group_create(SCALE_2D * HIT_BOX * 2,
			SCALE_2D * HIT_BOX * 2, 3);
	player = layer_create(game->mlx, SCALE_2D * HIT_BOX * 2,
			SCALE_2D * HIT_BOX * 2, 1);
	rotate = layer_create(game->mlx, SCALE_2D * HIT_BOX * 2,
			SCALE_2D * HIT_BOX * 2, 2);
	layer_group_add(cursor, player);
	layer_group_add(cursor, rotate);
	layer_stack_add(game->layers, cursor);
	draw_circle_fill(player, (t_vector2){SCALE_2D * HIT_BOX,
		SCALE_2D * HIT_BOX}, SCALE_2D * HIT_BOX,
		pixel_create(255, 0, 0, 255));
	if (WIDTH < 550 || HEIGHT < 550)
	{
		player->visible = false;
		rotate->visible = false;
	}
	return (cursor);
}

void	map_draw_init(t_game *game, t_layer *group, t_map *map_struct)
{
	t_layer	*map_mask;
	t_layer	*circle_map;
	t_layer	*raycast_debug;
	t_layer	*cursor;

	raycast_debug = layer_create(game->mlx,
			map_struct->width * SCALE_2D, map_struct->height * SCALE_2D, 5);
	map_mask = layer_create(game->mlx, MAP_SIZE, MAP_SIZE, 1);
	map_mask->mask = true;
	circle_map = layer_create(game->mlx, MAP_SIZE, MAP_SIZE, 3);
	layer_group_add(group, circle_map);
	layer_group_add(group, map_mask);
	layer_group_add(group, raycast_debug);
	draw_all_circle(circle_map, map_mask);
	cursor = add_player(game);
	layer_set_offset(cursor,
		(map_mask->width / 2) - SCALE_2D * HIT_BOX + MAP_OFFSET,
		(map_mask->width / 2) - SCALE_2D * HIT_BOX + MAP_OFFSET
		);
	if (WIDTH < MIN_WIDTH || HEIGHT < MIN_WIDTH)
	{
		circle_map->visible = false;
		map_mask->visible = false;
	}
}
