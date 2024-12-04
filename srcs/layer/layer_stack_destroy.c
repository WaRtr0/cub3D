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

void    layer_stack_destroy(void *mlx, t_layer_stack *stack)
{
    int i;
    t_layer *output_layer;

    if (!stack)
        return;
        
    printf("Destroying layer stack\n");
    output_layer = stack->output_layer;
    i = 0;
    while (i < stack->count)
    {
        if (stack->layers[i] && stack->layers[i] != output_layer)
        {
            layer_destroy(mlx, stack->layers[i]);
            stack->layers[i] = NULL;
        }
        i++;
    }
    
    if (output_layer)
    {
        layer_destroy(mlx, output_layer);
        stack->output_layer = NULL;
    }
    
    free(stack);
}