#include "draw.h"

void	draw_triangle(t_layer *layer, t_vector2 a, t_vector2 b, t_vector2 c,
		t_pixel color)
{
	draw_line(layer, a, b, color);
	draw_line(layer, b, c, color);
	draw_line(layer, c, a, color);
}