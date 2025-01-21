/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   layer_stack_add.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmorot <mmorot@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 00:18:15 by mmorot            #+#    #+#             */
/*   Updated: 2025/01/22 00:18:15 by mmorot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "layer.h"

static void	layer_stack_sort(t_layer_stack *stack)
{
	int		i;
	int		j;
	t_layer	*temp;

	if (!stack)
		return ;
	i = 0;
	while (i < stack->count - 1)
	{
		j = 0;
		while (j < stack->count - i - 1)
		{
			if (stack->layers[j]->z_index > stack->layers[j + 1]->z_index)
			{
				temp = stack->layers[j];
				stack->layers[j] = stack->layers[j + 1];
				stack->layers[j + 1] = temp;
			}
			j++;
		}
		i++;
	}
}

int	layer_stack_add(t_layer_stack *stack, t_layer *layer)
{
	if (!stack || !layer)
		return (0);
	if (stack->count >= stack->capacity)
		return (0);
	stack->layers[stack->count] = layer;
	stack->count++;
	layer_stack_sort(stack);
	return (1);
}
