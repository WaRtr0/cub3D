#include "game.h"
#include "layer.h"

static int	game_render(t_game *game)
{
	if (!game || !((!!game->layers) | game->is_running))
		return (0);
	if (game->update_callback)
		((void (*)(t_game *))game->update_callback)(game);
	layer_stack_render(game->layers, game->mlx, game->win);
	return (1);
}

int	game_run(t_game *game)
{
	if (!game || !game->mlx || !game->win)
		return (0);
	game->is_running = true;
	if (game->layers && game->layers->count > 0)
		game->layers->output_layer = layer_create(game->mlx,
				game->width, game->height, 0);
	mlx_loop_hook(game->mlx, &game_render, game);
	mlx_loop(game->mlx);
	return (1);
}
