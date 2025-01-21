/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   layer_dupe.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmorot <mmorot@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 00:17:49 by mmorot            #+#    #+#             */
/*   Updated: 2025/01/22 00:17:49 by mmorot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "layer.h"
#include "../libft/libft.h"
#include <../minilibx-linux/mlx.h>

int	layer_data_dupe(t_layer *src, unsigned int *dst)
{
	if (!src || !dst)
		return (0);
	ft_memcpy(dst, src->data, src->width * src->height * sizeof(unsigned int));
	return (1);
}

int	layer_dupe(t_layer *src, t_layer *dst)
{
	if (!src || !dst)
		return (0);
	dst->width = src->width;
	dst->height = src->height;
	dst->offset_x = src->offset_x;
	dst->offset_y = src->offset_y;
	dst->visible = src->visible;
	dst->bits_per_pixel = src->bits_per_pixel;
	dst->line_length = src->line_length;
	dst->endian = src->endian;
	dst->clear_color = src->clear_color;
	layer_data_dupe(src, dst->data);
	return (1);
}
