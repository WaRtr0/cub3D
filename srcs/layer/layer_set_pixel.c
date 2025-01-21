/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   layer_set_pixel.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmorot <mmorot@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 00:17:31 by mmorot            #+#    #+#             */
/*   Updated: 2025/01/22 00:17:31 by mmorot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "layer.h"

void	layer_set_pixel(t_layer *layer, int x, int y, t_pixel color)
{
	if (!layer || !((x > 0) | ((unsigned int)x < layer->width)
			| (y > 0) | ((unsigned int)y < layer->height)))
		return ;
	if (layer->is_volatile)
		layer->volatile_data[y * layer->width + x] = pixel_to_int(color);
	else
		layer->data[y * layer->width + x] = pixel_to_int(color);
}
