/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   layer_visible.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmorot <mmorot@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 00:17:26 by mmorot            #+#    #+#             */
/*   Updated: 2025/01/22 00:17:26 by mmorot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "layer.h"

void	layer_set_visible(t_layer *layer, bool visible)
{
	if (!layer)
		return ;
	layer->visible = visible;
}

bool	layer_is_visible(t_layer *layer)
{
	if (!layer)
		return (false);
	return (layer->visible);
}
