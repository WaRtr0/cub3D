#include "hook.h"
#include "layer.h"
#include "view.h"
#include "parsing.h"
#include "map.h"
#include "player.h"

int	frame_limit(void);

static void	check_move(int move_dir[4], t_game *game)
{
	if (move_dir[0] && !move_dir[1])
		player_move(game, game->data->yaw + 0);
	if (move_dir[1] && !move_dir[0])
		player_move(game, game->data->yaw + 180);
	if (move_dir[2] && !move_dir[3])
		player_move(game, game->data->yaw - 90);
	if (move_dir[3] && !move_dir[2])
		player_move(game, game->data->yaw + 90);
}

static void	update(t_game *game)
{
	if (game->player_state.key_yaw)
	{
		game->data->yaw += game->player_state.key_yaw * STEP_YAW;
		yaw_init(game);
	}
	if (frame_limit())
		check_move(game->player_state.move_dir, game);
	raycast(game);
	animate(game, -1, 2);
	if (CEIL_BONUS)
		draw_view_bonus(game, game->data);
	else
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


static void	draw_cursor(t_game *game)
{
	t_layer *group;
	t_layer *cursor;
	const int width = OUTPUT_WIDTH / RATIO;
	const int height = OUTPUT_HEIGHT / RATIO;

	group = layer_group_create(CURSOR_SIZE, CURSOR_SIZE, 1);
	if (!group)
	{
		game->is_running = false;
		return ;
	}
	cursor = layer_create(game->mlx, CURSOR_SIZE, CURSOR_SIZE, 1);
	draw_line(cursor, (t_vector2){.x=CURSOR_SIZE / 2, .y=0}, (t_vector2){.x=CURSOR_SIZE / 2, .y=CURSOR_SIZE} , pixel_create(0,0,0,255));
	draw_line(cursor, (t_vector2){.x=0, .y=CURSOR_SIZE / 2}, (t_vector2){.x=CURSOR_SIZE, .y=CURSOR_SIZE / 2} , pixel_create(0,0,0,255));
	layer_group_add(group, cursor);
	layer_stack_add(game->layers, group);
	layer_set_offset(group, (width / 2) - (CURSOR_SIZE / 2), (height / 2) - (CURSOR_SIZE / 2));
}

static void	init_layer(t_game *game)
{
	t_layer				*group;
	t_layer				*wall;
	const unsigned int	height = (OUTPUT_HEIGHT / RATIO);
	const unsigned int	width = (OUTPUT_WIDTH / RATIO);

	group = layer_stack_get(game->layers, 1);
	if (!group)
	{
		game->is_running = false;
		return ;
	}
	wall = layer_create(game->mlx, width, height, 2);
	if (!wall)
	{
		game->is_running = false;
		return ;
	}
	layer_group_add(group, wall);
	layer_volatile_on(wall);
	draw_cursor(game);
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
		return (game_destroy(game), 1);
	game_set_hook_press(game, hook_press);
	game_set_hook_release(game, hook_release);
	if (AUTO_CENTER_MOUSE)
		game_set_hook_mouse_move(game, hook_no_display_mouse_move);
	else
		game_set_hook_mouse_move(game, hook_display_mouse_move);
	game_set_update_callback(game, update);
	printf("hook\n");
	map_init(game->data->map, game);
	printf("map init\n");
	init_layer(game);
	printf("layer init\n");
	if (NO_DISPLAY_MOUSE)
		mlx_mouse_hide(game->mlx, game->win);
	game_run(game);
	game_destroy(game);
	return (0);
}
