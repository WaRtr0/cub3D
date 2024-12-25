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

static inline void get_depth_layer_color(t_layer_stack *stack, unsigned int x, unsigned int y, unsigned int *color)
{
    t_layer *layer;
    unsigned int pos;
    int i;
    t_dvector2 src;

    i = stack->count - 1;
    while (i >= 0)
    {
        layer = stack->layers[i];
        src.x = x - layer->offset_x;
        src.y = y - layer->offset_y;
        pos = src.y * layer->width + src.x;
        if (layer->mask)
        {
            if (!(pos < layer->width * layer->height && layer->data[pos] > 0 && (unsigned int)src.x <= layer->width))
                i--;
        }
        else if ((src.x >= 0) && (src.x < (int)layer->width) && (src.y >= 0) && (src.y < (int)layer->height))
        {
            if (layer->is_volatile)
            {
                if (blend_pixels(color, layer->volatile_data[pos]))
                {
                    layer->volatile_data[pos] = 0;
                    return ;
                }
                layer->volatile_data[pos] = 0;
            }
            if (blend_pixels(color, layer->data[pos]))
                return ;
        }
        i--;
    }
}

unsigned int ft_max(unsigned int x, unsigned int y) {
    if (x > y) {
        return x;
    }
    return y;
}

unsigned int ft_min(unsigned int x, unsigned int y) {
	if (x < y) {
		return x;
	}
	return y;
}


static void layer_group_render(t_layer *group, t_layer *output)
{
    unsigned int x;
    unsigned int stride;
    unsigned int start_x, end_x, start_y, end_y;

    if (!group || !output || group->type != GROUP_LAYER)
        return;

    start_x = ft_max(0, group->offset_x);
    end_x = ft_min(output->width, group->offset_x + group->width);
    start_y = ft_max(0, group->offset_y);
    end_y = ft_min(output->height, group->offset_y + group->height);

    while (start_y < end_y)
    {
        x = start_x;
        stride = start_y * output->width;
        while (x < end_x)
        {
            // if (y < output->height && x < output->width)
   				get_depth_layer_color(group->layers, x - group->offset_x, start_y - group->offset_y, (unsigned int *)&output->data[stride + x]);
            x++;
        }
        start_y++;
    }
}
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
	if ((output->width * output->height) % 2) {
        ((uint8_t *)output->data)[output->width * output->height - 1] = 0;
    }
}

static void ratio_transform(unsigned int *data)
{
	//Fonctionne que ratio 2
    unsigned int x;
    unsigned int y;
    unsigned int dest_x;
    unsigned int dest_y;
    unsigned int src_y;

    y = HEIGHT;
    while (y > 0)
    {
        x = WIDTH;
        src_y = y * OUTPUT_WIDTH;
        dest_y = y << 1;
        while (x > 0)
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

void layer_stack_render(t_layer_stack *stack, void *mlx, void *win)
{
    int i;

    if (!stack || !mlx || !win || !stack->output_layer || stack->count <= 0)
        return;

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

