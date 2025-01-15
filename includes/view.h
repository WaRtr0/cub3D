#ifndef VIEW_H
# define VIEW_H

# include "layer.h"
# include "utils.h"
# include "raycast.h"
# include "types.h"

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

typedef struct s_floor
{
	t_layer			*texture;
	unsigned int	height;
	unsigned int	width;
	unsigned int	width_tex;
	double			wall_prop;
	double			player_x;
	double			player_y;
	double			dir_x;
	double			dir_y;
	double			plane_x;
	double			plane_y;
	double			delta_x;
	double			delta_y;
	double			base_floor_x;
	double			base_floor_y;
	double			floor_step_x;
	double			floor_step_y;
	double			floor_x;
	double			floor_y;
	double			pos_x;
	double			pos_y;
}	t_floor;

typedef struct s_view
{
	t_layer			*render;
	t_layer			*background;
	t_ray			*ray;
	t_layer_stack	*textures;
	int				scale_3d;
	double			center;
	unsigned int	width;
	unsigned int	height;
	unsigned int	x;
	unsigned int	y;
	int				p;
	int				perceived_height;
	t_floor			floor;
}	t_view;

// delta_x = 2 * planeX * posZ_div_WIDTH;
// delta_y = 2 * planeY * posZ_div_WIDTH;

// base_floor_x = posZ * (dirX - planeX);
// base_floor_y = posZ * (dirY - planeY);

// floor_step_x = delta_x / abs(y / center);
// floor_step_y = delta_y / abs(y / center);

// floor_x = player_x + floor_x / abs(y / center);
// floor_y = player_y + floor_y / abs(y / center);

// pos_x = (WALL_PROP - WALL_HEIGHT) * player_x;
// pos_y = (WALL_PROP - WALL_HEIGHT) * player_y;

// tex_x = (int)((WALL_HEIGHT * floorX + pos_x)
//	* texture->width) % texture->width;

// tex_y = (int)((WALL_HEIGHT * floorY + pos_y)
//	* texture->height) % texture->height;

int		draw_view(t_game *game, t_game_data *raycast);
int		draw_view_bonus(t_game *game, t_game_data *raycast);
void	view_init_bonus(t_game *game, t_game_data *raycast, t_view *view);

#endif