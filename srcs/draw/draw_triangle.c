/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_triangle.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmorot <mmorot@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 00:19:15 by mmorot            #+#    #+#             */
/*   Updated: 2025/01/22 00:19:15 by mmorot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "draw.h"

void	draw_triangle(t_layer *layer, t_triangle_vector vector,
		t_pixel color)
{
	draw_line(layer, vector.a, vector.b, color);
	draw_line(layer, vector.b, vector.c, color);
	draw_line(layer, vector.c, vector.a, color);
}
