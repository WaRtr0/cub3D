/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   layer_stack_render.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmorot <mmorot@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 00:18:04 by mmorot            #+#    #+#             */
/*   Updated: 2025/01/22 00:18:05 by mmorot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

static void	fill_square(unsigned int *data, unsigned int src_value,
			unsigned int pos_x, unsigned int pos_y)
{
	int				dx;
	int				dy;
	unsigned int	dest;

	dy = 0;
	while (dy < RATIO)
	{
		dx = 0;
		while (dx < RATIO)
		{
			dest = (pos_y + dy) * OUTPUT_WIDTH + pos_x + dx;
			data[dest] = src_value;
			dx++;
		}
		dy++;
	}
}

static void	ratio_transform(unsigned int *data)
{
	t_dvector2					pos;
	t_dvector2					pre_y;
	unsigned int				src_value;
	static const unsigned int	width = OUTPUT_WIDTH / RATIO;

	pos.y = (OUTPUT_HEIGHT / RATIO);
	while (pos.y >= 0)
	{
		pos.x = width;
		pre_y.y = pos.y * RATIO;
		pre_y.x = pos.y * OUTPUT_WIDTH;
		while (pos.x >= 0)
		{
			src_value = data[pre_y.x + pos.x];
			fill_square(data, src_value, pos.x * RATIO, pre_y.y);
			pos.x--;
		}
		pos.y--;
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
