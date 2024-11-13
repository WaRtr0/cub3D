#include "game.h"

int game_handle_close(t_game *game)
{
    mlx_loop_end(game->mlx);
    return (0);
}

int game_handle_keypress(int keycode, t_game *game)
{
    if (game && game->hook_callback)
        ((void (*)(int, t_game *))game->hook_callback)(keycode, game);
}