#ifndef MAP_H
# define MAP_H

# include "game.h"
# include "types.h"

void	yaw_init(t_game *game);
void	map_init(t_map *map_struct, t_game *game);
void	map_draw_init(t_game *game, t_layer *group, t_map *map_struct);

#endif