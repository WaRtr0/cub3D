/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   layer_create.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmorot <mmorot@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 00:17:55 by mmorot            #+#    #+#             */
/*   Updated: 2025/01/22 00:17:55 by mmorot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "layer.h"
#include <stdlib.h>
#include <../minilibx-linux/mlx.h>
#include "../libft/libft.h"

t_layer	*layer_create(void *mlx, int width, int height, int z_index)
{
	t_layer	*layer;
	int		bits_per_pixel;
	int		line_length;
	int		endian;

	layer = (t_layer *)malloc(sizeof(t_layer));
	if (!layer)
		return (NULL);
	ft_bzero(layer, sizeof(t_layer));
	layer->width = width;
	layer->height = height;
	layer->z_index = z_index;
	layer->type = LAYER;
	layer->visible = true;
	layer->img = mlx_new_image(mlx, width, height);
	if (!layer->img)
	{
		free(layer);
		return (NULL);
	}
	layer->clear_color = pixel_create(0, 0, 0, 0);
	layer->data = (unsigned int *)mlx_get_data_addr(layer->img, &bits_per_pixel,
			&line_length, &endian);
	return (layer);
}
