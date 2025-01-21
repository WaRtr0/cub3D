/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_circle.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmorot <mmorot@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 00:19:32 by mmorot            #+#    #+#             */
/*   Updated: 2025/01/22 00:19:32 by mmorot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "draw.h"
#include "layer.h"

static void	set(int *x, int *y, int *p, int *radius)
{
	*x = 0;
	*y = *radius;
	*p = 3 - 2 * *radius;
}

void	draw_circle(t_layer *layer, t_vector2 center, int radius, t_pixel color)
{
	int	x;
	int	y;
	int	p;

	set(&x, &y, &p, &radius);
	while (x <= y)
	{
		layer_set_pixel(layer, center.x + x, center.y + y, color);
		layer_set_pixel(layer, center.x - x, center.y + y, color);
		layer_set_pixel(layer, center.x + x, center.y - y, color);
		layer_set_pixel(layer, center.x - x, center.y - y, color);
		layer_set_pixel(layer, center.x + y, center.y + x, color);
		layer_set_pixel(layer, center.x - y, center.y + x, color);
		layer_set_pixel(layer, center.x + y, center.y - x, color);
		layer_set_pixel(layer, center.x - y, center.y - x, color);
		if (p < 0)
			p += 4 * x + 6;
		else
		{
			p += 4 * (x - y) + 10;
			y--;
		}
		x++;
	}
}
