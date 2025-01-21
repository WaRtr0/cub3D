/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   layer_set_offset.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmorot <mmorot@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 00:17:33 by mmorot            #+#    #+#             */
/*   Updated: 2025/01/22 00:17:34 by mmorot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "layer.h"

void	layer_set_offset(t_layer *layer, int x, int y)
{
	if (layer == NULL)
		return ;
	layer->offset_x = x;
	layer->offset_y = y;
}
