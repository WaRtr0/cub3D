#include "view.h"
#include <math.h>
#include "layer.h"

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

static inline void	texture_pixel_vertical(t_view *view)
{
	t_pixel	pixel;
	t_floor	*floor_v;
	t_layer	*xpm;

	floor_v = &view->floor;
	if (view->p < 0)
		xpm = layer_stack_get(view->textures, CEILING_TEXTURE);
	else
		xpm = layer_stack_get(view->textures, FLOOR_TEXTURE);
	pixel = layer_get_pixel(xpm, ((int)((WALL_HEIGHT
						* floor_v->floor_x + floor_v->pos_x)
					* floor_v->width_tex)
				% floor_v->width_tex) / (double)floor_v->width_tex * xpm->width,
			((int)((WALL_HEIGHT * floor_v->floor_y + floor_v->pos_y)
					* floor_v->width_tex) % floor_v->width_tex)
			/ (double)floor_v->width_tex * xpm->height);
	pixel.a = 255;
	if ((pixel.r | pixel.g | pixel.b) == 0)
		pixel.a = 0;
	layer_set_pixel(view->render, view->x, view->y, pixel);
}

static inline void	view_init_floor_y(t_view *view)
{
	int	abs_p;

	abs_p = abs(view->p);
	view->floor.floor_step_x = view->floor.delta_x
		/ abs_p;
	view->floor.floor_step_y = view->floor.delta_y
		/ abs_p;
	view->floor.floor_x = view->floor.player_x
		+ view->floor.base_floor_x / abs_p;
	view->floor.floor_y = view->floor.player_y
		+ view->floor.base_floor_y / abs_p;
}

int	draw_view_bonus(t_game *game, t_game_data *raycast)
{
	t_view	view;

	view_init_bonus(game, raycast, &view);
	while (view.y < view.height)
	{
		view.p = view.y - raycast->center;
		view_init_floor_y(&view);
		view.x = 0;
		while (view.x < view.width)
		{
			view.perceived_height = view.scale_3d
				/ view.ray[view.x].distance / 2;
			if (view.y >= view.center - view.perceived_height
				&& view.y < raycast->center + view.perceived_height)
				texture_pixel_horizontal(&view);
			else
				texture_pixel_vertical(&view);
			view.floor.floor_x += view.floor.floor_step_x;
			view.floor.floor_y += view.floor.floor_step_y;
			view.x++;
		}
		view.y++;
	}
	return (0);
}
