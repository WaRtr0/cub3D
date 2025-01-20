#include "layer.h"

unsigned int	layer_get_width(t_layer *layer)
{
	if (!layer)
		return (0);
	return (layer->width);
}

unsigned int	layer_get_height(t_layer *layer)
{
	if (!layer)
		return (0);
	return (layer->height);
}
