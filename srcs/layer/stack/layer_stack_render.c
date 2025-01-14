#include "../libft/libft.h"
#include "layer.h"
#include <math.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>

static void	set_zero(t_layer *output)
{
	size_t		i;
	uint64_t	*output64;
	size_t		size64;

	output64 = (uint64_t *)output->data;
	size64 = (output->width * output->height) / 2;
	i = 0;
	while (i < size64)
	{
		output64[i] = 0;
		i++;
	}
	if ((output->width * output->height) % 2)
	{
		((uint8_t *)output->data)[output->width * output->height - 1] = 0;
	}
}

static void	ratio_transform(unsigned int *data)
{
	int	x;
	int	y;
	unsigned int	dest_x;
	unsigned int	dest_y;
	unsigned int	src_y;

	y = HEIGHT;
	while (y >= 0)
	{
		x = WIDTH;
		src_y = y * OUTPUT_WIDTH;
		dest_y = y << 1;
		while (x >= 0)
		{
			dest_x = x << 1;
			data[dest_y * OUTPUT_WIDTH + dest_x] = data[src_y + x];
			data[dest_y * OUTPUT_WIDTH + dest_x + 1] = data[src_y + x];
			data[(dest_y + 1) * OUTPUT_WIDTH + dest_x] = data[src_y + x];
			data[(dest_y + 1) * OUTPUT_WIDTH + dest_x + 1] = data[src_y + x];
			x--;
		}
		y--;
	}
}

void	layer_stack_render(t_layer_stack *stack, void *mlx, void *win)
{
	int	i;

	if (!stack || !mlx || !win || !stack->output_layer || stack->count <= 0)
		return ;
	set_zero(stack->output_layer);
	i = stack->count - 1;
	while (i >= 0)
	{
		if (stack->layers[i]->type == GROUP_LAYER)
			layer_group_render(stack->layers[i], stack->output_layer);
		i--;
	}
	if (RATIO > 1)
		ratio_transform(stack->output_layer->data);
	mlx_put_image_to_window(mlx, win, stack->output_layer->img, 0, 0);
}
