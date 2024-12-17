#include "layer.h"

t_layer	*layer_group_create(int width, int height, int z_index)
{
	t_layer	*group;

	group = (t_layer *)malloc(sizeof(t_layer));
	if (!group)
		return (NULL);
	group->type = GROUP_LAYER;
	group->width = width;
	group->height = height;
	group->z_index = z_index;
	group->offset_x = 0;
	group->offset_y = 0;
	group->layers = layer_stack_create();
	return (group);
}
