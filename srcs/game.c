
#include "game.h"
#include "layer.h"
#include "hook.h"
#include "string.h"

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
    game->update_callback = NULL;
    game->count = 0;
    
    return (game);
}

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

int game_init(t_game *game)
{
    if (!game)
    {
        printf("Game is NULL\n");
        return (0);
    }
    
    game->mlx = mlx_init();
    if (!game->mlx)
    {
        printf("Mlx is NULL\n");
        return (0);
    }
    
    game->win = mlx_new_window(game->mlx, game->width, game->height, game->title);
    if (!game->win)
    {
        printf("Window is NULL\n");
        return (0);
    }

    game->layers = layer_stack_create(5);  // Commencer avec 5 calques
    if (!game->layers)
    {
        printf("Layers is NULL\n");
        return (0);
    }
    
    // Setup event hooks
    mlx_hook(game->win, ON_KEYDOWN, MASK_KEY_PRESS, game_handle_keypress, game);    // Keypress
    mlx_hook(game->win, ON_DESTROY_NOTIFY, MASK_NO_EVENT, game_handle_close, game);          // Window close
    
    game->is_running = 1;
    game->last_frame = game_get_time();
    
    return (1);
}

void game_set_update_callback(t_game *game, void (*update)(t_game *))
{
    if (game)
        game->update_callback = (void *)update;
}

int game_render(t_game *game)
{
    if (!game || !game->layers)
        return (0);
    if (game->update_callback)
        ((void (*)(t_game *))game->update_callback)(game);
    layer_stack_render(game->layers, game->mlx, game->win);
    return (1);
}

int game_run(t_game *game)
{
    printf("Running game...\n");
    if (!game || !game->mlx || !game->win)
        return (0);
    
    game->is_running = 1;
    printf("Game is running...\n");
    

    mlx_loop_hook(game->mlx, &game_render, game);
    // printf("Mlx loop hook...\n");
    mlx_loop(game->mlx);

    // while (game->is_running)
    // {
    //     printf("Game loop...\n");
    //     game_calculate_delta_time(game);
    //     printf("Delta time: %f\n", game->delta_time);
    //     game_update(game);
    //     printf("Game updated...\n");
    //     game_render(game);
    //     printf("Game rendered...\n");
       
    //     printf("Mlx loop...\n");
    //      mlx_loop(game->mlx);
    // }
    
    return (1);
}

int game_handle_keypress(int keycode, t_game *game)
{
    if (game && game->hook_callback)
        ((void (*)(int, t_game *))game->hook_callback)(keycode, game);
}

void game_set_hook(t_game *game, void (*hook)(int, t_game *))
{
    if (game)
        game->hook_callback = (void *)hook;
}

int game_handle_close(t_game *game)
{
    mlx_loop_end(game->mlx);
    return (0);
}

double game_get_time(void)
{
    struct timeval tv;
    
    gettimeofday(&tv, NULL);
    return ((double)tv.tv_sec + (double)tv.tv_usec / 1000000.0);
}

void game_calculate_delta_time(t_game *game)
{
    if (!game)
        return;
    double current_time = game_get_time();
    game->delta_time = current_time - game->last_frame;
    game->last_frame = current_time;
}