#include "view.h"
#include "cub.h"
#include "game.h"
#include <float.h>
#include "utils.h"

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

// int	set_center(t_game *game, t_game_data *raycast, t_layer *background)
// {
// 	long long 	difftime;
// 	double		jump;

// 	jump = 0;
// 	raycast->center = game->height / 2 + raycast->pitch * 10;
// 	if (game->player_state.jumping != 0)
// 	{
// 		difftime = current_time() - game->player_state.jumping;  //BONUS
// 		if (difftime < 500)
// 			jump = 100 * (1 - pow(2 * (difftime / 500.0 - 0.5), 2));
// 		else
// 			game->player_state.jumping = 0;
// 	}
// 	raycast->center += jump;
// 	layer_set_offset(background, 0, SPLIT_HEIGHT + raycast->pitch * 10 + jump);
// 	return (0);
// }

int	draw_view(t_game *game, t_game_data *raycast, t_layer *render)
{
	t_layer *background;
	int		x;
	int		y;
	int		perceived_height;
	int		display_height;

	background = layer_stack_get(game->layers, 1);
	// warning change center get percent / 100. 0 => variable
	raycast->center = game->height / 2 + raycast->pitch * 10;
	layer_set_offset(background, 0, SPLIT_HEIGHT + raycast->pitch * 10);
	x = 0;
	
	while (x < game->width)
	{
		perceived_height = (int)(SCALE_3D / raycast->ray[x].distance) >> 1;
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
				(y - (raycast->center - perceived_height)) / (perceived_height * 2)));
			y++;
		}
		x++;
	}
	return (0);
}
