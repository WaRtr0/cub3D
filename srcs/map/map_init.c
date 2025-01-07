#include "cub.h"
#include "draw.h"
#include "game.h"
#include "hook.h"
#include "layer.h"
#include "types.h"
#include "view.h"
#include "raycast.h"
#include "parsing.h"
#include "player.h"
#include "utils.h"

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

void	map_init(t_map *map_struct, t_game *game)
{
    //group layer
    t_layer *group;
    t_layer *cursor;

    //layer
	t_layer *map;
	t_layer *map_mask;
	t_layer *circle_map;
	t_layer *player;
	t_layer *rotate;
    t_layer *raycast_debug;
	t_pixel	color;
	t_dvector2 pos = {0, 0};

	// game->data->map = map_struct;
    

    group = layer_group_create(MAP_SIZE,MAP_SIZE, 2);
    cursor = layer_group_create(SCALE_2D * HIT_BOX * 2,SCALE_2D * HIT_BOX * 2, 3);

    layer_stack_add(game->layers, group);
    layer_stack_add(game->layers, cursor);

	map = layer_create(game->mlx, map_struct->width * SCALE_2D, map_struct->height * SCALE_2D, 0);
    raycast_debug = layer_create(game->mlx,  map_struct->width * SCALE_2D, map_struct->height * SCALE_2D, 5);
	map_mask = layer_create(game->mlx, MAP_SIZE, MAP_SIZE, 1);
    map_mask->mask = true;
	circle_map = layer_create(game->mlx, MAP_SIZE, MAP_SIZE, 3);

	player = layer_create(game->mlx, SCALE_2D * HIT_BOX * 2, SCALE_2D * HIT_BOX * 2, 1);
	rotate = layer_create(game->mlx, SCALE_2D * HIT_BOX * 2, SCALE_2D * HIT_BOX * 2, 2);

	layer_group_add(group, circle_map);
	layer_group_add(group, map);
	layer_group_add(group, map_mask);
    layer_group_add(group, raycast_debug);

	layer_group_add(cursor, player);
	layer_group_add(cursor, rotate);

	layer_fill(map, pixel_create(125, 125, 125, 200));
	draw_circle_fill(map_mask, (t_vector2){MAP_SIZE / 2, MAP_SIZE / 2}, MAP_SIZE / 2, pixel_create(0, 0, 0, 255));

    draw_circle(circle_map, (t_vector2){MAP_SIZE / 2, MAP_SIZE / 2}, MAP_SIZE / 2 - 5, pixel_create(255, 255, 0, 255));
    draw_circle(circle_map, (t_vector2){MAP_SIZE / 2, MAP_SIZE / 2}, MAP_SIZE / 2 - 4, pixel_create(200, 200, 0, 255));
    draw_circle(circle_map, (t_vector2){MAP_SIZE / 2, MAP_SIZE / 2}, MAP_SIZE / 2 - 3, pixel_create(150, 150, 0, 255));
	draw_circle(circle_map, (t_vector2){MAP_SIZE / 2, MAP_SIZE / 2}, MAP_SIZE / 2 - 2, pixel_create(150, 150, 0, 255));
    draw_circle(circle_map, (t_vector2){MAP_SIZE / 2, MAP_SIZE / 2}, MAP_SIZE / 2 - 1, pixel_create(100, 100, 0, 255));
    draw_circle(circle_map, (t_vector2){MAP_SIZE / 2, MAP_SIZE / 2}, MAP_SIZE / 2, pixel_create(50, 50, 0, 255));

	draw_circle_fill(player, (t_vector2){SCALE_2D * HIT_BOX, SCALE_2D * HIT_BOX}, SCALE_2D * HIT_BOX, pixel_create(255, 0, 0, 255));
	// yaw(game);
	layer_set_offset(group, 25, 25);
	color = pixel_create(0, 0, 0, 255);
	for (pos.y = 0; pos.y < map_struct->height; pos.y++)
	{
		for (pos.x = 0; pos.x < map_struct->width; pos.x++)
		{
			if (map_struct->tiles[pos.y * map_struct->width + pos.x] == W)
				draw_rect_fill(map, (t_vector2){pos.x * SCALE_2D, pos.y * SCALE_2D},
					(t_vector2){(pos.x + 1) * SCALE_2D, (pos.y + 1) * SCALE_2D}, color);
			else if (map_struct->tiles[pos.y * map_struct->width + pos.x] == P)
			{	
				game->data->player.x = pos.x;
				game->data->player.y = pos.y;
			}
			draw_rect(map, (t_vector2){pos.x * SCALE_2D, pos.y * SCALE_2D},
				(t_vector2){(pos.x + 1) * SCALE_2D, (pos.y + 1) * SCALE_2D}, pixel_create(0, 0, 0, 175));
		}
	}
	layer_set_offset(cursor, 
		map_mask->width/2 - SCALE_2D * HIT_BOX + group->offset_x,
		map_mask->height/2 - SCALE_2D * HIT_BOX + group->offset_y
	);
	center_offset_player_on_map(game);
    layer_volatile_on(map);

    if (WIDTH < 275*2 || HEIGHT < 275*2)
    {
        circle_map->visible = false;
        map_mask->visible = false;
        rotate->visible = false;
        player->visible = false;
        map->visible = false;
    }
}
