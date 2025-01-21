/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   layer_group_destroy.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmorot <mmorot@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 00:18:27 by mmorot            #+#    #+#             */
/*   Updated: 2025/01/22 00:18:28 by mmorot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "layer.h"

void	layer_group_destroy(void *mlx, t_layer *group)
{
	int		i;
	t_layer	*child;

	if (!group || group->type != GROUP_LAYER || !group->layers)
		return ;
	i = 0;
	while (i < group->layers->count)
	{
		child = group->layers->layers[i];
		if (child)
		{
			if (child->type == GROUP_LAYER)
				layer_group_destroy(mlx, child);
			else
				layer_destroy(mlx, child);
			group->layers->layers[i] = NULL;
		}
		i++;
	}
	layer_stack_destroy(mlx, group->layers);
	group->layers = NULL;
	free(group);
	group = NULL;
}
