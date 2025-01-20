#include "layer.h"

void	layer_set_mask(t_layer *layer, bool mask)
{
	if (!layer)
		return ;
	layer->mask = mask;
}

bool	layer_is_mask(t_layer *layer)
{
	if (!layer)
		return (false);
	return (layer->mask);
}
