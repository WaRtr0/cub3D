/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   layer_get_offset.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmorot <mmorot@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 00:17:44 by mmorot            #+#    #+#             */
/*   Updated: 2025/01/22 00:17:44 by mmorot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "layer.h"

void	layer_get_offset(t_layer *layer, int *x, int *y)
{
	if (!layer)
		return ;
	*x = layer->offset_x;
	*y = layer->offset_y;
}

int	layer_offset_x(t_layer *layer)
{
	if (!layer)
		return (0);
	return (layer->offset_x);
}

int	layer_offset_y(t_layer *layer)
{
	if (!layer)
		return (0);
	return (layer->offset_y);
}
