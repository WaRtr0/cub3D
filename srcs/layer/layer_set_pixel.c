#include "layer.h"

void	layer_set_pixel(t_layer *layer, int x, int y, t_pixel color)
{
	if (x < 0 || x >= layer->width || y < 0 || y >= layer->height)
		return ;
	layer->data[y * layer->width + x] = pixel_to_int(color);
}