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

t_pixel	texture_pixel(t_layer *xpm, double x_ratio, double y_ratio)
{
	t_pixel	pixel;

	pixel = layer_get_pixel(xpm, x_ratio * xpm->width, y_ratio * xpm->height);
	return (pixel);
}

int	draw_view(t_game *game, t_game_data *raycast)
{
	t_layer *group;
	t_layer *render;
	t_layer *background;
	unsigned int scale_3d = game->scale_3d;
	int		x;
	int		y;
	int		perceived_height;
	int		display_height;


	group = layer_stack_get(game->layers, 1);
	raycast = game->data;
	render = layer_group_get(group, 2);
	background = layer_group_get(group, 1);
	// warning change center get percent / 100. 0 => variable
	raycast->center = ((HEIGHT >> 1) + (raycast->pitch * HEIGHT_PERC));
	layer_set_offset(background, 0, SPLIT_HEIGHT + raycast->pitch * HEIGHT_PERC);
	x = 0;
	
	while (x < WIDTH)
	{
		perceived_height = (int)(scale_3d / raycast->ray[x].distance) >> 1;
		y = raycast->center - perceived_height;
		if (raycast->center - perceived_height < 0)
			y = 0;
		if (raycast->center + perceived_height > game->height)
			display_height = game->height;
		else
			display_height = raycast->center + perceived_height;
		while (y < display_height)
		{
			/*if ((int)raycast->ray[x].percent == 0 || (int)raycast->ray[x].percent == 100)
				layer_set_pixel(render, x, y, pixel_create(0, 0, 0, 255));*/
			layer_set_pixel(render, x, y,
				texture_pixel(layer_stack_get(game->textures, raycast->ray[x].face),
				raycast->ray[x].percent / 100.,
				(y - (raycast->center - perceived_height)) / (perceived_height << 1)));
			y++;
		}
		x++;
	}
	return (0);
}
