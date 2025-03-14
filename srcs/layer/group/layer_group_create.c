/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   layer_group_create.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmorot <mmorot@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 00:18:34 by mmorot            #+#    #+#             */
/*   Updated: 2025/01/22 00:18:35 by mmorot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "layer.h"

t_layer	*layer_group_create(int width, int height, int z_index)
{
	t_layer	*group;

	group = (t_layer *)malloc(sizeof(t_layer));
	if (!group)
		return (NULL);
	group->type = GROUP_LAYER;
	group->width = width;
	group->height = height;
	group->z_index = z_index;
	group->offset_x = 0;
	group->offset_y = 0;
	group->visible = true;
	group->layers = NULL;
	group->layers = layer_stack_create();
	if (!group->layers)
	{
		free(group);
		return (NULL);
	}
	return (group);
}
