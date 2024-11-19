#include "cub.h"
#include "draw.h"
#include "game.h"
#include "hook.h"
#include "layer.h"
#include "types.h"

static void	update(t_game *game)
{
	(void)game;
	// update script
}

static void	hook(int keycode, t_game *game)
{
	t_layer	*sprite;

	(void)game;
	(void)keycode;
	// hook script
	// example move sprite
	sprite = layer_stack_get(game->layers, 1);
	if (keycode == KEY_RIGHT)
	{
		layer_set_offset(sprite, sprite->offset_x + 50, sprite->offset_y);
	}
	if (keycode == KEY_LEFT)
	{
		layer_set_offset(sprite, sprite->offset_x - 50, sprite->offset_y);
	}
	if (keycode == KEY_UP)
	{
		layer_set_offset(sprite, sprite->offset_x, sprite->offset_y - 50);
	}
	if (keycode == KEY_DOWN)
	{
		layer_set_offset(sprite, sprite->offset_x, sprite->offset_y + 50);
	}
	// stop game
	if (keycode == KEY_ESC)
		game_handle_close(game);
}

	// fake parsings
static t_map	*get_parsed_map(void)
{
	t_map	*map;
	t_map_tile	*tiles;

	map = (t_map *)malloc(sizeof(t_map));
	map->width = 10;
	map->height = 10;
	tiles = (t_map_tile *)malloc(sizeof(t_map_tile) * map->width * map->height);
	
	map->tiles = tiles;

	static const t_map_tile map_tile[10][10] = {
		{W, W, W, W, W, W, W, W, W, W},
		{W, E, E, W, W, E, E, E, E, W},
		{W, E, E, E, W, E, E, E, E, W},
		{W, E, E, E, W, W, W, E, E, W},
		{W, E, E, E, E, W, E, E, E, W},
		{W, E, E, P, E, E, E, E, E, W},
		{W, E, E, E, E, E, W, E, E, W},
		{W, E, E, E, E, E, W, D, W, W},
		{W, E, E, E, E, E, W, E, E, W},
		{W, W, W, W, W, W, W, W, W, W},
	};
	
	 for (int y = 0; y < map->height; y++) {
        for (int x = 0; x < map->width; x++) {
        tiles[y * map->width + x] = map_tile[y][x]; // Indexation 1D
        }
    }
	return (map);
}

static void center_offset_player_on_map(t_game *game)
{
	t_layer *player;
	t_layer *map;
	map = layer_stack_get(game->layers, 100);
	player = layer_stack_get(game->layers, 102);
	layer_set_offset(map, player->offset_x * , player->offset_y * SCALE_2D);

}

static void generate_map(t_map *map_struct, t_game *game)
{
	t_layer *map;
	t_layer *map_mask;
	t_layer *player;
	t_pixel	color;
	t_dvector2 pos = {0, 0};
	t_dvector2 pos_player = {0, 0};
	map = layer_create(game->mlx, map_struct->width * SCALE_2D, map_struct->height * SCALE_2D, 100);
	player = layer_create(game->mlx, SCALE_2D, SCALE_2D, 102);
	map->mask = true;
	map_mask = layer_create(game->mlx, 250, 250, 101);
	layer_stack_add(game->layers, map);
	layer_stack_add(game->layers, map_mask);
	layer_stack_add(game->layers, player);

	layer_fill(map, pixel_create(125, 125, 125, 200));
	draw_circle_fill(map_mask, (t_vector2){125, 125}, 125, pixel_create(0, 0, 0, 255));
	draw_circle_fill(player, (t_vector2){SCALE_2D / 2, SCALE_2D / 2}, SCALE_2D / 2, pixel_create(255, 0, 0, 255));
	// layer_set_offset(map, 25, 25);
	layer_set_offset(map_mask, 25, 25);
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
				layer_set_offset(player, pos.x * SCALE_2D, pos.y * SCALE_2D);
				pos_player.x = pos.x;
				pos_player.y = pos.y;
			}
		}
	}
	center_offset_player_on_map(game);
}

int	main(void)
{
	t_game *game;
	t_layer *background;
	t_layer *sprite;
	t_layer *sprite_mask;
	t_pixel bg_color;
	t_pixel sprite_color;

	game = game_new(1920, 1080, "My Game !");
	if (!game)
		return (1);
	game_set_hook(game, hook);
	game_set_update_callback(game, update);
	background = layer_create(game->mlx, game->width, game->height, 0);
	sprite = layer_create(game->mlx, 500, 500, 1);
	sprite_mask = layer_create(game->mlx, 500, 500, 2);
	sprite->mask = true;

	draw_circle_fill(sprite_mask, (t_vector2){250, 250}, 250, pixel_create(0, 0, 0, 255));
	draw_xpm_texture(game->mlx, sprite, (t_vector2){0, 0},
		"assets/textures/test.xpm");

	
	layer_stack_add(game->layers, background);
	layer_stack_add(game->layers, sprite);
	layer_stack_add(game->layers, sprite_mask);
	
	

	
	layer_set_offset(sprite, game->width / 2 - 500, game->height / 2 - 500);
	bg_color = pixel_create(255, 255, 255, 255);
	layer_fill(background, bg_color);
	
	generate_map(get_parsed_map(), game);
	sprite_color = pixel_create(255, 0, 0, 255);
	draw_triangle_fill(background, (t_vector2){game->width / 4, game->height
		/ 4}, (t_vector2){game->width / 4 * 3, game->height / 4},
		(t_vector2){game->width / 4 * 2, game->width / 4 * 2}, pixel_create(0,
			255, 255, 255));
	game_run(game);
	game_destroy(game);
	return (0);
}