#include "view.h"
#include "cub.h"
#include "game.h"
#include <float.h>

void	layer_split(t_layer *layer, t_pixel color1, t_pixel color2)
{
    int x;
    int y;

	y = 0;
	while (y < layer->height / 2)
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


#include "draw.h"
int	draw_view(t_game *game)
{
	t_layer *render;
	t_layer *background;
	t_game_data *raycast;

	int		x;
	int		y;
	int		perceived_height;


	raycast = game->data;
	render = layer_stack_get(game->layers, 2);
	background = layer_stack_get(game->layers, 1);
	// warning change center get percent / 100. 0 => variable
	raycast->center = game->height / 2 + raycast->pitch * 10;
	layer_set_offset(background, 0, SPLIT_HEIGHT + raycast->pitch * 10);
	x = 0;
	
	while (x < game->width)
	{
		perceived_height = (int)(SCALE_3D / raycast->ray[x].distance) >> 1;
		y = raycast->center - perceived_height;
		while (y < raycast->center + perceived_height)
		{
			//layer_set_pixel(render, x, y, pixel_create(255, 0, 0, 255));
			/*if ((int)raycast->ray[x].percent == 0 || (int)raycast->ray[x].percent == 100)
				layer_set_pixel(render, x, y, pixel_create(0, 0, 0, 255));*/
			layer_set_pixel(render, x, y,
				texture_pixel(layer_stack_get(game->textures, raycast->ray[x].face),
				raycast->ray[x].percent / 100.,
				(y - (raycast->center - perceived_height)) / (perceived_height * 2)));
			y++;
		}
		x++;
	}
	return (0);
}

// int	create_view(t_game *game)
// {
// 	t_layer	*background;
// 	t_view	view;
	
// 	t_layer *stupid_test = layer_create(game->mlx, game->width, game->height, 0);
// 	layer_stack_add(game->layers, stupid_test);
	
// 	background = layer_create(game->mlx, game->width, game->height, 0);
// 	layer_split(background, pixel_create(45, 0, 190, 255), pixel_create(40, 40, 40, 255));
// 	layer_stack_add(game->layers, background);
// 	return (0);
// }