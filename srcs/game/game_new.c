#include "game.h"
#include "math.h"
#include "../libft/libft.h"

t_game	*game_new(int width, int height, char *title)
{
	t_game	*game;

	game = (t_game *)malloc(sizeof(t_game));
	if (!game)
		return (NULL);
	game->data = (t_game_data *)malloc(sizeof(t_game_data));
	if (!game->data)
	{
		free(game);
		return (NULL);
	}
	game->data->player.x = 0;
	game->data->player.y = 0;
	game->data->pitch = 0;
	game->data->yaw = 0;
	game->data->is_warping = false;
	game->data->map = NULL;
	game->width = width;
	game->height = height;
	game->title = title;
	game->is_running = 0;
	// (((WIDTH / 2) / tan((FOV / 2) * M_PI / 180)) * WALL_HEIGHT)
	game->scale_3d = (((WIDTH >> 1) / tan((FOV >> 1) * M_PI / 180)) * WALL_HEIGHT);
	game->delta_time = 0.0;
	game->last_frame = 0.0;
	game->mlx = NULL;
	game->win = NULL;
	game->hook_callback = NULL;
	game->hook_release = NULL;
	game->hook_mouse_move = NULL;
	game->hook_mouse_press = NULL;
	game->layers = NULL;
	game->textures = NULL;
	game->update_callback = NULL;
	game->count = 0;
	game->player_state.running = 0;
	if (game_init(game) == 0)
	{
		free(game);
		return (NULL);
	}
	return (game);
}
