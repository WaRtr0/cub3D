#include "layer.h"

t_pixel	layer_get_pixel(t_layer *layer, int x, int y)
{
	int	index;

	if (x - layer->offset_x < 0 || x - layer->offset_x >= (int)layer->width || y
		- layer->offset_y < 0 || y - layer->offset_y >= (int)layer->height)
		return (pixel_create(0, 0, 0, 0));
	index = (y - layer->offset_y) * (int)layer->width + (x - layer->offset_x);
	return (int_to_pixel(layer->data[index]));
}