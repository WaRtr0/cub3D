#include "../libft/libft.h"
#include "layer.h"
#include <math.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>

static inline int	blend_pixels(unsigned int *dst, unsigned int s)
{
	const unsigned int	d = *dst;
	const unsigned int	d_a = d >> 24;
	const unsigned int	s_a = s >> 24;
	unsigned int		final;

	if (!s_a)
		return (d_a == 255);
	if (!d_a)
		return (*dst = s, s_a == 255);
	if (d_a == 255)
		return (1);
	final = d_a + ((s_a * (255 - d_a)) + 127) / 255;
	if (!final)
		return (*dst = 0, 0);
	*dst = (final << 24) | ((((((d >> 16) & 0xFF) * d_a * 255
						+ ((s >> 16) & 0xFF) * s_a * (255 - d_a)) + (255
						* final >> 1)) / (255
					* final)) << 16) | ((((((d >> 8) & 0xFF) * d_a * 255
						+ ((s >> 8) & 0xFF) * s_a * (255 - d_a)) + (255
						* final >> 1)) / (255 * final)) << 8) | (((((d & 0xFF)
						* d_a * 255 + (s & 0xFF) * s_a * (255 - d_a)) + (255
						* final >> 1)) / (255 * final)));
	return (final == 255);
}

static inline unsigned int	get_depth_layer_color(t_layer_stack *stack,
		unsigned int x, unsigned int y)
{
	t_layer			*layer;
	unsigned int	color;
	unsigned int	pos;
	int				i;
	t_dvector2		src;

	color = 0;
	i = stack->count - 1;
	while (i >= 0)
	{
		layer = stack->layers[i];
		src.x = x - layer->offset_x;
		src.y = y - layer->offset_y;
		pos = src.y * layer->width + src.x;
		if (layer->mask)
		{
			if (!(pos < layer->width * layer->height && layer->data[pos] > 0
					&& src.x <= layer->width))
				i--;
		}
		else if ((src.x >= 0) && (src.x < (int)layer->width) && (src.y >= 0)
			&& (src.y < (int)layer->height))
		{
			if (layer->is_volatile)
			{
				if (blend_pixels(&color, layer->volatile_data[pos]))
				{
					layer->volatile_data[pos] = 0;
					return (color);
				}
				layer->volatile_data[pos] = 0;
			}
			if (blend_pixels(&color, layer->data[pos]))
				return (color);
		}
		i--;
	}
	return (color);
}

void	layer_stack_render(t_layer_stack *stack, void *mlx, void *win)
{
	int						i;
	register unsigned int	x;
	register unsigned int	y;

	if (!stack || !mlx || !win || stack->count <= 0 || !stack->output_layer
		|| !stack->layers)
		return ;
	y = 0;
	while (y < stack->output_layer->height)
	{
		x = 0;
		while (x < stack->output_layer->width)
		{
			stack->output_layer->data[y * stack->output_layer->width
				+ x] = get_depth_layer_color(stack, x, y);
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(mlx, win, stack->output_layer->img, 0, 0);
}
