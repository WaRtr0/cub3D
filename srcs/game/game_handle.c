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

int game_handle_krelease(int keycode, t_game *game)
{
    if (game && game->hook_release)
        ((void (*)(int, t_game *))game->hook_release)(keycode, game);
}

int game_handle_mouse_move(int x, int y, t_game *game)
{
    if (game && game->hook_mouse_move)
        ((void (*)(int, int, t_game *))game->hook_mouse_move)(x, y, game);
}

int game_handle_mouse_press(int button, int x, int y, t_game *game)
{
    if (game && game->hook_mouse_press)
        ((void (*)(int, int, int, t_game *))game->hook_mouse_press)(button, x, y, game);
}