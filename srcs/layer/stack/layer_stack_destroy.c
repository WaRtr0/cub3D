/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   layer_stack_destroy.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmorot <mmorot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 00:18:09 by mmorot            #+#    #+#             */
/*   Updated: 2025/01/22 17:23:01 by mmorot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "layer.h"
#include <stdlib.h>
#include <stdio.h>

// void    layer_stack_destroy(void *mlx, t_layer_stack *stack)
// {
//     int i;
//     int is_output_in_layers;
//     if (!stack)
//         return;
//     is_output_in_layers = 0;
//     i = 0;
//     while (i < stack->count)
//     {
//         if (stack->layers[i])
//         {
//             if (stack->layers[i] == stack->output_layer)
//                 is_output_in_layers = 1;
//             layer_destroy(mlx, stack->layers[i]);
//             stack->layers[i] = NULL;
//         }
//         i++;
//     }
//     if (stack->output_layer && !is_output_in_layers)
//     {
//         layer_destroy(mlx, stack->output_layer);
//         stack->output_layer = NULL;
//     }
//     free(stack);
// }

static void	wrapper_output_layer_destroy(void *mlx, t_layer **output_layer)
{
	if (*output_layer)
	{
		layer_destroy(mlx, *output_layer);
		*output_layer = NULL;
	}
}

void	layer_stack_destroy(void *mlx, t_layer_stack *stack)
{
	int		i;
	t_layer	*output_layer;

	if (!stack)
		return ;
	output_layer = stack->output_layer;
	i = 0;
	while (i < stack->count)
	{
		if (stack->layers[i] && stack->layers[i] != output_layer)
		{
			if (stack->layers[i]->type == GROUP_LAYER)
				layer_group_destroy(mlx, stack->layers[i]);
			else
				layer_destroy(mlx, stack->layers[i]);
			stack->layers[i] = NULL;
		}
		i++;
	}
	wrapper_output_layer_destroy(mlx, &output_layer);
	free(stack);
	stack = NULL;
}
