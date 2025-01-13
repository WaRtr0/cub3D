#include "layer.h"

void	layer_split_fill(t_layer *layer, t_pixel color1, t_pixel color2)
{
	unsigned int	x;
	unsigned int	y;

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
