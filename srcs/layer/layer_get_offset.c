#include "layer.h"

void	layer_get_offset(t_layer *layer, int *x, int *y)
{
	if (!layer)
		return ;
	*x = layer->offset_x;
	*y = layer->offset_y;
}
