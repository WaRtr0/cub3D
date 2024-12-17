#include "layer.h"
#include <stdlib.h>
#include <../minilibx-linux/mlx.h>


t_layer	*layer_create(void *mlx, int width, int height, int z_index)
{
	t_layer	*layer;
	int		bits_per_pixel;
	int		line_length;
	int		endian;

	layer = (t_layer *)malloc(sizeof(t_layer));
	if (!layer)
		return (NULL);
	layer->width = width;
	layer->height = height;
	layer->z_index = z_index;
	layer->offset_x = 0;
	layer->offset_y = 0;
	layer->type = LAYER;
	layer->mask = false;
	layer->visible = true;
	layer->is_volatile = false;
	layer->volatile_update = NULL;
	layer->volatile_data = NULL;
	layer->img = mlx_new_image(mlx, width, height);
	if (!layer->img)
	{
		free(layer);
		return (NULL);
	}
	layer->clear_color = pixel_create(0, 0, 0, 0);
	layer->data = (unsigned int *)mlx_get_data_addr(layer->img, &bits_per_pixel,
			&line_length, &endian);
	return (layer);
}
