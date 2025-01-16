#include "game.h"
#include "hook.h"
#include "player.h"
#include "layer.h"

static inline void	center_offset_player_on_map(t_game *game)
{
	t_layer						*group;
	t_layer						*map;
	t_layer						*map_mask;
	static const unsigned int	scale_2d = (SIZE_2D / RATIO);

	group = layer_stack_get(game->layers, 2);
	map = layer_group_get(group, 0);
	map_mask = layer_group_get(group, 1);
	layer_set_offset(map,
		(map_mask->width >> 1) - (
			game->data->player.x * scale_2d) - (scale_2d >> 1),
		(map_mask->height >> 1) - (
			game->data->player.y * scale_2d) - (scale_2d >> 1)
		);
}

void	hook_press(int keycode, t_game *game)
{
	if (keycode == KEY_RIGHT)
		game->data->player.x += 1;
	if (keycode == KEY_LEFT)
		game->data->player.x -= 1;
	if (keycode == KEY_UP)
		game->data->player.y -= 1;
	if (keycode == KEY_DOWN)
		game->data->player.y += 1;
	if ((keycode >= KEY_LEFT) | (keycode <= KEY_DOWN))
		center_offset_player_on_map(game);
	if (keycode == KEY_W)
		game->player_state.move_dir = 1;
	if (keycode == KEY_S)
		game->player_state.move_dir = -1;
	if (keycode == KEY_SPACE)
		interact_door(game, 1);
	if (keycode == KEY_SHIFT)
		game->player_state.running = 1;
	if (keycode == KEY_ESC)
		game_handle_close(game);
}
