/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   layer_destroy.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmorot <mmorot@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 00:17:52 by mmorot            #+#    #+#             */
/*   Updated: 2025/01/22 00:17:52 by mmorot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "layer.h"
#include <../minilibx-linux/mlx.h>
#include <stdlib.h>
#include <stdio.h>
// void	layer_destroy(void *mlx, t_layer *layer)
// {
// 	if (!layer)
// 		return ;
// 	if (layer->img)
// 		mlx_destroy_image(mlx, layer->img);
// 	free(layer);
// }

void	layer_destroy(void *mlx, t_layer *layer)
{
	if (!layer)
		return ;
	printf("Destroying layer %d\n", layer->z_index);
	if (layer->is_volatile == true && layer->volatile_data)
	{
		free(layer->volatile_data);
		layer->volatile_data = NULL;
	}
	if (layer->img)
	{
		mlx_destroy_image(mlx, layer->img);
		layer->img = NULL;
	}
	free(layer);
	layer = NULL;
}
