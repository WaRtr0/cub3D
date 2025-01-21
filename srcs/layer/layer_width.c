/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   layer_width.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmorot <mmorot@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 00:17:20 by mmorot            #+#    #+#             */
/*   Updated: 2025/01/22 00:17:20 by mmorot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "layer.h"

unsigned int	layer_get_width(t_layer *layer)
{
	if (!layer)
		return (0);
	return (layer->width);
}

unsigned int	layer_get_height(t_layer *layer)
{
	if (!layer)
		return (0);
	return (layer->height);
}
