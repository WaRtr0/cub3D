#include "layer.h"

void	layer_clear(t_layer *layer)
{
	if (!layer)
		return ;
	layer_fill(layer, layer->clear_color);
}
