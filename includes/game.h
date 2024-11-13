
#ifndef GAME_H
# define GAME_H

# include "types.h"
# include <../minilibx-linux/mlx.h>
# include <math.h>
# include <stdio.h>
# include <stdlib.h>

# include <time.h>

// Constructor & Destructor
t_game	*game_new(int width, int height, char *title);
void	game_destroy(t_game *game);

// Core methods
int		game_init(t_game *game);
int		game_run(t_game *game);
void	game_set_update_callback(t_game *game, void (*update)(t_game *));
// void    game_render(t_game *game);

// Event handlers
int		game_handle_keypress(int keycode, t_game *game);
int		game_handle_close(t_game *game);
void	game_set_hook(t_game *game, void (*hook)(int, t_game *));
// void

// Utility functions
double	game_get_time(void);
void	game_calculate_delta_time(t_game *game);

#endif
