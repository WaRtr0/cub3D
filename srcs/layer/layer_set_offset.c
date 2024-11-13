#include "layer.h"

void	layer_set_offset(t_layer *layer, int x, int y)
{
	if (!layer)
		return ;
	layer->offset_x = x;
	layer->offset_y = y;
}