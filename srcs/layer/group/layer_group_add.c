#include "layer.h"

int	layer_group_add(t_layer *group, t_layer *layer)
{
	if (!group || !layer || group->type != GROUP_LAYER)
		return (0);
	return (layer_stack_add(group->layers, layer));
}
