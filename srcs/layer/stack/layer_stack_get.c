/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   layer_stack_get.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmorot <mmorot@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 00:18:07 by mmorot            #+#    #+#             */
/*   Updated: 2025/01/22 00:18:07 by mmorot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "layer.h"

t_layer	*layer_stack_get(t_layer_stack *stack, int z_index)
{
	int	i;

	if (!stack)
		return (NULL);
	i = 0;
	while (i < stack->count)
	{
		if (stack->layers[i]->z_index == z_index)
			return (stack->layers[i]);
		i++;
	}
	return (NULL);
}
