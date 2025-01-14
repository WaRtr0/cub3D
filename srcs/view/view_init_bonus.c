#include "view.h"
#include <math.h>
#include "layer.h"

static void	floor_init(t_game *game, t_floor	*floor)
{
	const double	yaw_rad = (double)game->data->yaw * M_RAD;
	const double	tan_half_fov = tan(((double)FOV / 2.0) * M_RAD);
	const double	pos_z = 0.5 * HEIGHT;
	const double	posz_div_width = pos_z / WIDTH;

	floor->texture = layer_stack_get(game->textures, CEILING_TEXTURE);
	floor->width = floor->texture->width;
	floor->player_x = game->data->player.x + 0.5;
	floor->player_y = game->data->player.y + 0.5;
	floor->dir_x = cos(yaw_rad);
	floor->dir_y = sin(yaw_rad);
	floor->plane_x = -floor->dir_y * tan_half_fov;
	floor->plane_y = floor->dir_x * tan_half_fov;
	floor->delta_x = 2 * floor->plane_x * posz_div_width;
	floor->delta_y = 2 * floor->plane_y * posz_div_width;
	floor->base_floor_x = pos_z * (floor->dir_x - floor->plane_x);
	floor->base_floor_y = pos_z * (floor->dir_y - floor->plane_y);
	floor->pos_x = (WALL_PROP - WALL_HEIGHT) * floor->player_x;
	floor->pos_y = (WALL_PROP - WALL_HEIGHT) * floor->player_y;
}

void	view_init_bonus(t_game *game, t_game_data *raycast, t_view *view)
{
	t_layer	*group;
	t_layer	*background;

	group = layer_stack_get(game->layers, 1);
	background = layer_group_get(group, 1);
	layer_set_offset(background, 0, SPLIT_HEIGHT
		+ raycast->pitch * HEIGHT_PERC);
	view->render = layer_group_get(group, 2);
	view->ray = raycast->ray;
	view->scale_3d = game->scale_3d;
	raycast->center = ((HEIGHT >> 1) + (raycast->pitch * HEIGHT_PERC));
	view->center = raycast->center;
	view->x = 0;
	view->y = 0;
	view->textures = game->textures;
	floor_init(game, &view->floor);
}
