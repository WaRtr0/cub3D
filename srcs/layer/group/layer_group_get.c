/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   layer_group_get.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmorot <mmorot@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 00:18:21 by mmorot            #+#    #+#             */
/*   Updated: 2025/01/22 00:18:21 by mmorot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "layer.h"

t_layer	*layer_group_get(t_layer *group, int z_index)
{
	if (!group || group->type != GROUP_LAYER || group->layers == NULL)
		return (NULL);
	return (layer_stack_get(group->layers, z_index));
}
