#include "layer.h"
#include <../minilibx-linux/mlx.h>

void	layer_destroy(void *mlx, t_layer *layer)
{
	if (!layer)
		return ;
	if (layer->img)
		mlx_destroy_image(mlx, layer->img);
	free(layer);
}