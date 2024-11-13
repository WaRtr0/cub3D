#include "game.h"
#include "layer.h"

void game_destroy(t_game *game)
{
    if (!game)
        return;
    
    if (game->layers)
        layer_stack_destroy(game->mlx, game->layers);
    if (game->win)
        mlx_destroy_window(game->mlx, game->win);
    if (game->mlx)
    {
        mlx_destroy_display(game->mlx);
        free(game->mlx);
    }
    free(game);
}