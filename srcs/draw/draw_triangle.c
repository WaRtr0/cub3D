#include "draw.h"

void	draw_triangle(t_layer *layer, t_triangle_vector vector,
		t_pixel color)
{
	draw_line(layer, vector.a, vector.b, color);
	draw_line(layer, vector.b, vector.c, color);
	draw_line(layer, vector.c, vector.a, color);
}
