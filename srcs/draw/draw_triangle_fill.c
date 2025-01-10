#include "draw.h"
#include "layer.h"
#include <math.h>

static float	calc_area(t_vector2 p1, t_vector2 p2, t_vector2 p3)
{
	return ((p2.x - p1.x) * (p3.y - p1.y) - (p2.y - p1.y) * (p3.x - p1.x));
}

static t_draw_triangle_fill	init_triangle_fill(t_triangle_vector vector)
{
	t_draw_triangle_fill	tri;


	tri.min.x = floorf(fminf(fminf(vector.a.x, vector.b.x), vector.c.x));
	tri.min.y = floorf(fminf(fminf(vector.a.y, vector.b.y), vector.c.y));
	tri.max.x = ceilf(fmaxf(fmaxf(vector.a.x, vector.b.x), vector.c.x));
	tri.max.y = ceilf(fmaxf(fmaxf(vector.a.y, vector.b.y), vector.c.y));
	tri.area = calc_area(vector.a, vector.b, vector.c);

	tri.p.x = tri.min.x;
	tri.p.y = tri.min.y;
	return (tri);
}

void	draw_triangle_fill(t_layer *layer, t_triangle_vector vector,
		t_pixel color)
{
	t_draw_triangle_fill	tri;

	tri = init_triangle_fill(vector);
	while (tri.p.x <= tri.max.x)
	{
		tri.p.y = tri.min.y;
		while (tri.p.y <= tri.max.y)
		{
			tri.area1 = calc_area(tri.p, vector.a, vector.b);
			tri.area2 = calc_area(tri.p, vector.b, vector.c);
			tri.area3 = calc_area(tri.p, vector.c, vector.a);
			if ((tri.area >= 0 && tri.area1 >= 0
					&& tri.area2 >= 0 && tri.area3 >= 0)
				|| (tri.area <= 0 && tri.area1 <= 0
					&& tri.area2 <= 0 && tri.area3 <= 0))
			{
				layer_set_pixel(layer, tri.p.x, tri.p.y, color);
			}
			tri.p.y++;
		}
		tri.p.x++;
	}
}
