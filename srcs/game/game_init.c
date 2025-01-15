#include "game.h"
#include "hook.h"
#include "layer.h"

int	game_init(t_game *g)
{
	if (!g)
		return (0);
	g->mlx = mlx_init();
	if (!g->mlx)
		return (0);
	g->win = mlx_new_window(g->mlx, g->width, g->height, g->title);
	if (!g->win)
		return (0);
	g->layers = layer_stack_create();
	if (!g->layers)
		return (0);
	g->textures = layer_stack_create();
	if (!g->textures)
		return (0);
	mlx_hook(g->win, ON_KEYDOWN, MASK_KEY_PRESS, game_handle_keypress, g);
	mlx_hook(g->win, ON_DESTROY_NOTIFY, MASK_NO_EVENT, game_handle_close, g);
	mlx_hook(g->win, ON_KEYUP, MASK_KEY_RELEASE, game_handle_krelease, g);
	mlx_hook(g->win, ON_MOUSE_MOVE, MASK_POINTER_MOTION,
		game_handle_mouse_move, g);
	mlx_hook(g->win, ON_MOUSE_DOWN, MASK_BUTTON_PRESS,
		game_handle_mouse_press, g);
	return (1);
}
