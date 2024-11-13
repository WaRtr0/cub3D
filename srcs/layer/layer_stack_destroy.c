#include "layer.h"
#include <stdlib.h>

void	layer_stack_destroy(void *mlx, t_layer_stack *stack)
{
	int	i;

	if (!stack)
		return ;
	i = 0;
	while (i < stack->count)
	{
		if (stack->layers[i])
		{
			layer_destroy(mlx, stack->layers[i]);
			stack->layers[i] = NULL;
		}
		i++;
	}
	if (stack->output_layer)
		layer_destroy(mlx, stack->output_layer);
	free(stack);
}