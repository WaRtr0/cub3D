#include "view.h"
#include "layer.h"
#include "math.h"

static inline void	texture_pixel_horizontal(t_view *view)
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
}

static inline void	view_init(t_game *game, t_game_data *raycast, t_view *view)
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
}

int	draw_view(t_game *game, t_game_data *raycast)
{
	t_view	view;

	view_init(game, raycast, &view);
	while (view.y < HEIGHT)
	{
		view.p = view.y - raycast->center;
		view.x = 0;
		while (view.x < WIDTH)
		{
			view.perceived_height = view.scale_3d
				/ view.ray[view.x].distance / 2;
			if (view.y >= view.center - view.perceived_height
				&& view.y < raycast->center + view.perceived_height)
				texture_pixel_horizontal(&view);
			view.x++;
		}
		view.y++;
	}
	return (0);
}
