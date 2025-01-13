#include "layer.h"
#include <stdint.h>

static void	fill_remaining(t_layer *layer, unsigned int fill_color)
{
	if ((layer->width * layer->height) % 2)
		layer->data[layer->width * layer->height - 1] = fill_color;
}

void	layer_fill(t_layer *layer, t_pixel color)
{
	unsigned int	fill_color;
	uint64_t		fill_color64;
	uint64_t		*data64;
	size_t			count64;
	size_t			i;

	if (!layer)
		return ;
	fill_color = pixel_to_int(color);
	fill_color64 = ((uint64_t)fill_color << 32) | fill_color;
	data64 = (uint64_t *)layer->data;
	count64 = (layer->width * layer->height) / 2;
	i = 0;
	while (i < count64)
	{
		data64[i] = fill_color64;
		i++;
	}
	fill_remaining(layer, fill_color);
}
