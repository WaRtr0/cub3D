/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   layer_mask.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmorot <mmorot@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 00:17:39 by mmorot            #+#    #+#             */
/*   Updated: 2025/01/22 00:17:39 by mmorot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "layer.h"

void	layer_set_mask(t_layer *layer, bool mask)
{
	if (!layer)
		return ;
	layer->mask = mask;
}

bool	layer_is_mask(t_layer *layer)
{
	if (!layer)
		return (false);
	return (layer->mask);
}
