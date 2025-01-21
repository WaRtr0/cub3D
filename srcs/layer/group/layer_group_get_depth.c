/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   layer_group_get_depth.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmorot <mmorot@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 00:18:24 by mmorot            #+#    #+#             */
/*   Updated: 2025/01/22 00:18:25 by mmorot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "layer.h"

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

static inline int	layer_is_not_masked(t_layer *layer,
	unsigned int pos, unsigned int *color)
{
	if (layer->is_volatile)
	{
		if (blend_pixels(color, layer->volatile_data[pos]))
		{
			layer->volatile_data[pos] = 0;
			return (1);
		}
		layer->volatile_data[pos] = 0;
	}
	if (blend_pixels(color, layer->data[pos]))
		return (1);
	return (0);
}

void	get_depth_layer_color(t_layer_stack *stack, unsigned int x,
			unsigned int y, unsigned int *color)
{
	t_handle_depth	h;

	h.i = stack->count - 1;
	while (h.i >= 0)
	{
		h.layer = stack->layers[h.i];
		h.src.x = x - h.layer->offset_x;
		h.src.y = y - h.layer->offset_y;
		h.pos = h.src.y * h.layer->width + h.src.x;
		if (h.layer->mask)
		{
			if (!((h.pos < h.layer->width * h.layer->height)
					&& ((t_layer *)h.layer)->data[h.pos] > 0
					&& (unsigned int)h.src.x <= h.layer->width))
				h.i--;
		}
		else if ((h.src.x >= 0) && (h.src.x < (int)h.layer->width)
			&& (h.src.y >= 0) && (h.src.y < (int)h.layer->height))
		{
			if (layer_is_not_masked(h.layer, h.pos, color))
				return ;
		}
		h.i--;
	}
}
