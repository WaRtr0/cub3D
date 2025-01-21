/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   layer_group_add.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmorot <mmorot@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 00:18:37 by mmorot            #+#    #+#             */
/*   Updated: 2025/01/22 00:18:37 by mmorot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "layer.h"

int	layer_group_add(t_layer *group, t_layer *layer)
{
	if (!group || !layer || group->type != GROUP_LAYER)
		return (0);
	return (layer_stack_add(group->layers, layer));
}
