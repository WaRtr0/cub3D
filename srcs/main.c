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
#include "map.h"

static void	update(t_game *game)
{
	raycast(game);
	draw_view(game, game->data);
	if (DEBUG)
	{
		game->count++;
		if (game->count >= MAX_FRAME)
		{
			game_handle_close(game);
		}
	}
}

static void	init_layer(t_game *game)
{
	t_layer	*group;
	t_layer	*wall;

	group = layer_stack_get(game->layers, 1);
	wall = layer_create(game->mlx, WIDTH, HEIGHT, 2);
	layer_group_add(group, wall);
	layer_volatile_on(wall);
}

static int	check_and_parse(int argc, char **argv, t_game *game)
{
	if (argc == 2)
	{
		if (!parse(game, argv[1]))
			return (1);
	}
	else
	{
		prerr("Error: Invalid number of arguments\n");
		return (1);
	}
	return (0);
}

int	main(int argc, char **argv)
{
	t_game	*game;

	game = game_new(OUTPUT_WIDTH, OUTPUT_HEIGHT, GAME_NAME);
	if (!game || check_and_parse(argc, argv, game))
		return (1);
	game_set_hook_press(game, hook_press);
	game_set_hook_release(game, hook_release);
	if (NO_DISPLAY_MOUSE)
		game_set_hook_mouse_move(game, hook_no_display_mouse_move);
	else
		game_set_hook_mouse_move(game, hook_display_mouse_move);
	game_set_update_callback(game, update);
	map_init(game->data->map, game);
	init_layer(game);
	if (NO_DISPLAY_MOUSE)
		mlx_mouse_hide(game->mlx, game->win);
	game_run(game);
	game_destroy(game);
	return (0);
}
