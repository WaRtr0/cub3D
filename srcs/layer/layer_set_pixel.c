#include "layer.h"

void	layer_set_pixel(t_layer *layer, int x, int y, t_pixel color)
{
	// fix unsigned changer prototype
	if (x < 0 || (unsigned int)x >= layer->width || y < 0 || (unsigned int)y >= layer->height)
		return ;
	if (layer->is_volatile)
		layer->volatile_data[y * layer->width + x] = pixel_to_int(color);
	else
		layer->data[y * layer->width + x] = pixel_to_int(color);
}
