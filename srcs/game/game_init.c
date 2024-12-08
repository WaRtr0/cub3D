#include "game.h"
#include "hook.h"
#include "layer.h"

int game_init(t_game *game)
{
    if (!game)
    {
        printf("Game is NULL\n");
        return (0);
    }
    game->mlx = mlx_init();
    if (!game->mlx)
        return (0);
    game->win = mlx_new_window(game->mlx, game->width, game->height, game->title);
    if (!game->win)
        return (0);
    game->layers = layer_stack_create();
    if (!game->layers)
        return (0);
    game->textures = layer_stack_create();
    if (!game->textures)
        return (0);
    mlx_hook(game->win, ON_KEYDOWN, MASK_KEY_PRESS, game_handle_keypress, game);
    mlx_hook(game->win, ON_DESTROY_NOTIFY, MASK_NO_EVENT, game_handle_close, game);
    mlx_hook(game->win, ON_KEYUP, MASK_KEY_RELEASE, game_handle_krelease, game);
    mlx_hook(game->win, ON_MOUSE_MOVE, MASK_POINTER_MOTION, game_handle_mouse_move, game);
    mlx_hook(game->win, ON_MOUSE_DOWN, MASK_BUTTON_PRESS, game_handle_mouse_press, game);
    // mlx_hook(game->win, ON_MOUSE_UP, MASK_BUTTON_RELEASE, game_handle_mouse_press, game);

    game->is_running = 1;
    game->last_frame = game_get_time();
    return (1);
}