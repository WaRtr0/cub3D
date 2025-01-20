#include "layer.h"

void	layer_set_visible(t_layer *layer, bool visible)
{
	if (!layer)
		return ;
	layer->visible = visible;
}

bool	layer_is_visible(t_layer *layer)
{
	if (!layer)
		return (false);
	return (layer->visible);
}
