#ifndef VIEW_H
# define VIEW_H

# include "layer.h"
# include "utils.h"
# include "raycast.h"

// typedef struct s_view
// {
// 	t_raycast	raycasts;
// 	int			center;
// 	int			width;
// 	int			height;
// 	double		wall_height;
// }	t_view;

// int		create_view(t_game *game);
// t_view	get_view(t_game *game, t_raycast raycasts);
int		draw_view(t_game *game);

#endif