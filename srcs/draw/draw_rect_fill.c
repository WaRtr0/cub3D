/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_rect_fill.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmorot <mmorot@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 00:19:26 by mmorot            #+#    #+#             */
/*   Updated: 2025/01/22 00:19:27 by mmorot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "draw.h"
#include "layer.h"

void	draw_rect_fill(t_layer *layer, t_vector2 start, t_vector2 end,
		t_pixel color)
{
	int	x;
	int	y;

	x = start.x;
	while (x <= end.x)
	{
		y = start.y;
		while (y <= end.y)
		{
			layer_set_pixel(layer, x, y, color);
			y++;
		}
		x++;
	}
}
