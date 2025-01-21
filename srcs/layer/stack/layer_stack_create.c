/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   layer_stack_create.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmorot <mmorot@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 00:18:12 by mmorot            #+#    #+#             */
/*   Updated: 2025/01/22 00:18:13 by mmorot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "layer.h"
#include "../libft/libft.h"
#include <stdlib.h>

t_layer_stack	*layer_stack_create(void)
{
	t_layer_stack	*stack;

	stack = (t_layer_stack *)malloc(sizeof(t_layer_stack));
	if (!stack)
		return (NULL);
	stack->output_layer = NULL;
	stack->count = 0;
	stack->capacity = LAYER_STACK_CAPACITY;
	ft_bzero(stack->layers, LAYER_STACK_CAPACITY * sizeof(t_layer *));
	return (stack);
}
