#include "draw.h"
#include "layer.h"
#include <math.h>

static float	calc_area(t_vector2 p1, t_vector2 p2, t_vector2 p3)
{
	return (p2.x - p1.x) * (p3.y - p1.y) - (p2.y - p1.y) * (p3.x - p1.x);
}

void	draw_triangle_fill(t_layer *layer, t_vector2 a, t_vector2 b,
		t_vector2 c, t_pixel color)
{
	t_draw_triangle_fill	triangle;

	triangle.min.x = floorf(fminf(fminf(a.x, b.x), c.x));
	triangle.min.y = floorf(fminf(fminf(a.y, b.y), c.y));
	triangle.max.x = ceilf(fmaxf(fmaxf(a.x, b.x), c.x));
	triangle.max.y = ceilf(fmaxf(fmaxf(a.y, b.y), c.y));
	triangle.area = calc_area(a, b, c);
	for (triangle.p.x = triangle.min.x; triangle.p.x <= triangle.max.x; triangle.p.x++)
	{
		for (triangle.p.y = triangle.min.y; triangle.p.y <= triangle.max.y; triangle.p.y++)
		{
			triangle.area1 = calc_area(triangle.p, a, b);
			triangle.area2 = calc_area(triangle.p, b, c);
			triangle.area3 = calc_area(triangle.p, c, a);
			if ((triangle.area >= 0 && triangle.area1 >= 0
					&& triangle.area2 >= 0 && triangle.area3 >= 0)
				|| (triangle.area <= 0 && triangle.area1 <= 0
					&& triangle.area2 <= 0 && triangle.area3 <= 0))
			{
				layer_set_pixel(layer, triangle.p.x, triangle.p.y, color);
			}
		}
	}
}
