#include "game.h"

t_game *game_new(int width, int height, char *title)
{
    t_game *game;

    game = (t_game *)malloc(sizeof(t_game));
    if (!game)
        return (NULL);
    game->width = width;
    game->height = height;
    game->title = title;
    game->is_running = 0;
    game->delta_time = 0.0;
    game->last_frame = 0.0;
    game->mlx = NULL;
    game->win = NULL;
    game->hook_callback = NULL;
    game->layers = NULL;
    game->texture = NULL;
    game->update_callback = NULL;
    game->count = 0;
    if (game_init(game) == 0)
    {
        free(game);
        return (NULL);
    }
    return (game);
}