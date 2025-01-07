#include "hook.h"
#include "game.h"

void	hook_release(int keycode, t_game *game)
{
	if (keycode == KEY_SHIFT)
	{
		game->player_state.running = 0;
	}
}
