#include "hook.h"
#include "game.h"

void	hook_release(int keycode, t_game *game)
{
	if (keycode == KEY_SHIFT)
		game->player_state.running = 0;
	if (keycode == KEY_W)
		game->player_state.move_dir[0] = 0;
	if (keycode == KEY_S)
		game->player_state.move_dir[1] = 0;
	if (keycode == KEY_A)
		game->player_state.move_dir[2] = 0;
	if (keycode == KEY_D)
		game->player_state.move_dir[3] = 0;
	if (keycode == KEY_LEFT || keycode == KEY_RIGHT)
		game->player_state.key_yaw = 0;
}
