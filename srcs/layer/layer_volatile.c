#include "layer.h"
#include "../libft/libft.h"

void	layer_volatile_on(t_layer *layer)
{
	if (layer->is_volatile)
		return ;
	layer->is_volatile = true;
	layer->volatile_data = ft_calloc(layer->width
			* layer->height, sizeof(unsigned int));
	if (!layer->volatile_data)
	{
		layer->is_volatile = false;
		layer->volatile_data = NULL;
	}
}

void	layer_volatile_off(t_layer *layer)
{
	if (!layer->is_volatile)
		return ;
	layer->is_volatile = false;
	free(layer->volatile_data);
	layer->volatile_data = NULL;
}
