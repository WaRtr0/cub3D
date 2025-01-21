/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   layer_volatile.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmorot <mmorot@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 00:17:23 by mmorot            #+#    #+#             */
/*   Updated: 2025/01/22 00:17:23 by mmorot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "layer.h"
#include "../libft/libft.h"

void	layer_volatile_on(t_layer *layer)
{
	if (!layer)
		return ;
	if (layer->is_volatile)
		return ;
	layer->is_volatile = true;
	layer->volatile_data = ft_calloc(layer->width
			* layer->height, sizeof(unsigned int));
	if (!layer->volatile_data)
	{
		layer->is_volatile = false;
		layer->volatile_data = NULL;
	}
}

void	layer_volatile_off(t_layer *layer)
{
	if (!layer)
		return ;
	if (!layer->is_volatile)
		return ;
	layer->is_volatile = false;
	free(layer->volatile_data);
	layer->volatile_data = NULL;
}
