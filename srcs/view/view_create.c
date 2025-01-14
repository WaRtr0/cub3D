#include "view.h"

void	layer_split(t_layer *layer, t_pixel color1, t_pixel color2)
{
	unsigned int x;
	unsigned int y;

	y = 0;
	while (y < layer->height >> 1)
	{
		x = 0;
		while (x < layer->width)
			layer_set_pixel(layer, x++, y, color1);
		y++;
	}
	while (y < layer->height)
	{
		x = 0;
		while (x < layer->width)
			layer_set_pixel(layer, x++, y, color2);
		y++;
	}
}
#include <math.h>
#include <stdio.h>
t_pixel	texture_pixel(t_layer *xpm, double x_ratio, double y_ratio)
{
	t_pixel	pixel;

	pixel = layer_get_pixel(xpm, floor(x_ratio * (double)xpm->width), y_ratio * xpm->height);
	pixel.a = 255;
	return (pixel);
}


t_pixel	texture_pixel_horizontal(t_view *view)
{
	t_pixel	pixel;
	t_layer	*xpm;

	xpm = layer_stack_get(view->textures, view->ray[view->x].face);
	pixel = layer_get_pixel(xpm, floor(view->ray[view->x].percent / 100.
				* (double)xpm->width), (view->y
				- (view->center - view->perceived_height))
			/ (view->perceived_height << 1) * xpm->height);
	pixel.a = 255;
	layer_set_pixel(view->render, view->x, view->y, pixel);
	return (pixel);
}
t_pixel texture_pixel_vertical(t_view *view)
{
    t_pixel pixel;
    t_floor *floor_v;
    t_layer *xpm;

	floor_v = &view->floor;
	xpm = layer_stack_get(view->textures, CEILING_TEXTURE);
    pixel = layer_get_pixel(xpm, ((int)((WALL_HEIGHT * floor_v->floor_x + floor_v->pos_x) * floor_v->width) % floor_v->width) / (double)floor_v->width * xpm->width, ((int)((WALL_HEIGHT * floor_v->floor_y + floor_v->pos_y) * floor_v->width) % floor_v->width) / (double)floor_v->width * xpm->height);
    pixel.a = 255;
	if ((pixel.r | pixel.g | pixel.b) == 0)
		pixel.a = 0;
    layer_set_pixel(view->render, view->x, view->y, pixel);
    return pixel;
}


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

static void view_init(t_game *game, t_game_data *raycast, t_view *view)
{
	t_layer *group;
	t_layer *background;

	group = layer_stack_get(game->layers, 1);
	background = layer_group_get(group, 1);
	layer_set_offset(background, 0, SPLIT_HEIGHT + raycast->pitch * HEIGHT_PERC);
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

int draw_view(t_game *game, t_game_data *raycast)
{
	t_view	view;

	view_init(game, raycast, &view);
	while (view.y < HEIGHT)
	{
		view.p = view.y - raycast->center;
		view.floor.floor_step_x = view.floor.delta_x / abs(view.p);
		view.floor.floor_step_y = view.floor.delta_y / abs(view.p);
		view.floor.floor_x = view.floor.player_x + view.floor.base_floor_x / abs(view.p);
		view.floor.floor_y = view.floor.player_y + view.floor.base_floor_y / abs(view.p);
		view.x = 0;
		while (view.x < WIDTH)
		{
			view.perceived_height = view.scale_3d / view.ray[view.x].distance / 2;
			if (view.y >= view.center - view.perceived_height && view.y < raycast->center + view.perceived_height)
			{
				texture_pixel_horizontal(&view);
			}
			else if (CEIL_BONUS)
			{
				texture_pixel_vertical(&view);
			}
			view.floor.floor_x += view.floor.floor_step_x;
			view.floor.floor_y += view.floor.floor_step_y;
			view.x++;
		}
		view.y++;
	}
	return (0);
}
