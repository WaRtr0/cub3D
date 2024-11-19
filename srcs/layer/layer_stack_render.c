#include "layer.h"
#include <math.h>
#include <stdint.h>


static void	blend_pixels(unsigned int *dst, unsigned int src)
{
	unsigned char	alpha;
	float			a;
	unsigned char	r;
	unsigned char	g;
	unsigned char	b;

	alpha = (src >> 24) & 0xFF;
	if (alpha == 255)
		*dst = src;
	else if (alpha > 0)
	{
		a = alpha / 255.0f;
		r = ((src >> 16) & 0xFF) * a + ((*dst >> 16) & 0xFF) * (1.0f - a);
		g = ((src >> 8) & 0xFF) * a + ((*dst >> 8) & 0xFF) * (1.0f - a);
		b = (src & 0xFF) * a + (*dst & 0xFF) * (1.0f - a);
		*dst = (255 << 24) | (r << 16) | (g << 8) | b;
	}
}

static void	process_row(t_layer *layer, t_layer *output, int y, int start_x)
{
	int				x;
	int				src_y;
	int				src_x;
	unsigned int	current;

	src_y = y - layer->offset_y;
	x = start_x;
	while (x < output->width && x < layer->offset_x + layer->width)
	{
		src_x = x - layer->offset_x;
		if (src_x >= 0 && src_x < layer->width)
		{
			current = layer->data[src_y * layer->width + src_x];
			if ((current >> 24) & 0xFF)
				blend_pixels(&output->data[y * output->width + x], current);
		}
		x++;
	}
}

static void process_row_mask(t_layer *layer, t_layer *output, t_layer *mask, int y, int start_x)
{
	int				x;
	int				src_y;
	int				src_x;
	unsigned int	current;
	unsigned int	mask_pixel;

	src_y = y - layer->offset_y;
	x = start_x;
	while (x < output->width && x < layer->offset_x + layer->width)
	{
		src_x = x - layer->offset_x;
		if (src_x >= 0 && src_x < layer->width)
		{
			current = layer->data[src_y * layer->width + src_x];
			mask_pixel = mask->data[(y - mask->offset_y) * mask->width + (x - mask->offset_x)];
			if ((current >> 24) & 0xFF && (mask_pixel >> 24) & 0xFF)
				blend_pixels(&output->data[y * output->width + x], current);
		}
		x++;
	}
}

static void	blend_layer_to_output(t_layer *layer, t_layer *output)
{
	int	y;
	int	start_y;
	int	start_x;

	if (!layer->visible)
		return ;
	start_y = fmax(0, layer->offset_y);
	start_x = fmax(0, layer->offset_x);
	y = start_y;
	while (y < output->height && y < layer->offset_y + layer->height)
	{
		if (y - layer->offset_y >= 0 && y - layer->offset_y < layer->height)
			process_row(layer, output, y, start_x);
		y++;
	}
}

static void blend_layer_mask_to_output(t_layer *layer, t_layer *output, t_layer *mask)
{
	int	y;
	int	start_y;
	int	start_x;

	if (!mask->visible)
		return ;
	start_y = fmax(0, mask->offset_y);
	start_x = fmax(0, mask->offset_x);
	y = start_y;
	while (y < output->height && y < layer->offset_y + layer->height && y < mask->offset_y + mask->height)
	{
		if (y - layer->offset_y >= 0 && y - layer->offset_y < layer->height && y - mask->offset_y >= 0 && y - mask->offset_y < mask->height)
			process_row_mask(layer, output, mask, y, start_x);
		y++;
	}
}

static void	copy_background(t_layer *output, t_layer *bg)
{
	size_t		i;
	uint64_t	*output64;
	uint64_t	*bg64;
	size_t		size64;

	output64 = (uint64_t *)output->data;
	bg64 = (uint64_t *)bg->data;
	size64 = (output->width * output->height) / 2;
	i = 0;
	while (i < size64)
	{
		output64[i] = bg64[i];
		i++;
	}
	if ((output->width * output->height) % 2)
		output->data[output->width * output->height
			- 1] = bg->data[output->width * output->height - 1];
}

void	layer_stack_render(t_layer_stack *stack, void *mlx, void *win)
{
	int	i;

	if (!stack || !mlx || !win || stack->count == 0 || !stack->output_layer)
		return ;
	copy_background(stack->output_layer, stack->layers[0]);
	i = 1;
	while (i < stack->count)
	{
		if (stack->layers[i] && !stack->layers[i]->mask)
			blend_layer_to_output(stack->layers[i], stack->output_layer);
		else if (stack->layers[i] && stack->layers[i]->mask && ++i < stack->count && stack->layers[i])
			blend_layer_mask_to_output(stack->layers[i - 1], stack->output_layer, stack->layers[i]);
		i++;
	}
	mlx_put_image_to_window(mlx, win, stack->output_layer->img, 0, 0);
}
