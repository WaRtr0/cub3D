#include "game.h"

void game_set_update_callback(t_game *game, void (*update)(t_game *))
{
    if (game)
        game->update_callback = (void *)update;
}


void game_set_hook(t_game *game, void (*hook)(int, t_game *))
{
    if (game)
        game->hook_callback = (void *)hook;
}