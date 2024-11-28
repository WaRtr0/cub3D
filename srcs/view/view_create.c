#include "view.h"
#include "cub.h"
#include "game.h"

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

int	draw_view(t_game *game)
{
	t_layer *render;
	t_layer *background;
	t_game_data *raycast;

	int		x;
	int		y;
	int		perceived_height;

	t_pixel SUD = pixel_create(0, 0, 255, 255); // Blue
	t_pixel OUEST = pixel_create(0, 255, 0, 255); // Green
	t_pixel NORD = pixel_create(255, 0, 0, 255); // Red
	t_pixel EST = pixel_create(255, 0, 255, 255); // Purple


	raycast = game->data;
	render = layer_stack_get(game->layers, 2);
	background = layer_stack_get(game->layers, 1);
	// warning change center get percent 0 => variable
	raycast->center = game->height / 2 + raycast->pitch * 10;
	layer_set_offset(background, 0, SPLIT_HEIGHT + raycast->pitch * 10);
	x = 0;
	
	while (x < game->width)
	{
		perceived_height = (int)(SCALE_3D / raycast->ray[x].distance);
		y = raycast->center - perceived_height / 2;
		while (y < raycast->center + perceived_height / 2)
		{
			// layer_set_pixel(render, x, y++, pixel_create(255, 0, 0, 255));
			if (raycast->ray[x].face == N_FACE)
				layer_set_pixel(render, x, y++, NORD);
			else if (raycast->ray[x].face == S_FACE)
				layer_set_pixel(render, x, y++, SUD);
			else if (raycast->ray[x].face == E_FACE)
				layer_set_pixel(render, x, y++, EST);
			else if (raycast->ray[x].face == O_FACE)
				layer_set_pixel(render, x, y++, OUEST);
			else
				y++;

			if ((int)raycast->ray[x].percent == 0 || (int)raycast->ray[x].percent == 100)
				layer_set_pixel(render, x, y++, pixel_create(0, 0, 0, 255));
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