#include "game.h"

void	game_set_update_callback(t_game *game, void (*update)(t_game *))
{
	if (game)
		game->update_callback = (void *)update;
}


void	game_set_hook_press(t_game *game, void (*hook)(int, t_game *))
{
	if (game)
		game->hook_callback = (void *)hook;
}

void	game_set_hook_release(t_game *game, void (*hook)(int, t_game *))
{
	if (game)
		game->hook_release = (void *)hook;
}

void	game_set_hook_mouse_move(t_game *game, void (*hook)(int, int, t_game *))
{
	if (game)
		game->hook_mouse_move = (void *)hook;
}


void	game_set_hook_mouse_press(t_game *game, void (*hook)
	(int, int, t_game *))
{
	if (game)
		game->hook_mouse_press = (void *)hook;
}
