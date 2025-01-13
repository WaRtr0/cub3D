#include "layer.h"

t_layer	*layer_group_get(t_layer *group, int z_index)
{
	if (!group || group->type != GROUP_LAYER || group->layers == NULL)
		return (NULL);
	return (layer_stack_get(group->layers, z_index));
}
