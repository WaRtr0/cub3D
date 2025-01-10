#include "draw.h"

static void	set(int *x, int *y, int *p, int *radius)
{
	*x = 0;
	*y = *radius;
	*p = 3 - 2 * *radius;
}

void	draw_circle_fill(t_layer *layer, t_vector2 center, int radius,
		t_pixel color)
{
	int	x;
	int	y;
	int	p;

	set(&x, &y, &p, &radius);
	while (x <= y)
	{
		draw_line(layer, (t_vector2){center.x - x, center.y + y},
			(t_vector2){center.x + x, center.y + y}, color);
		draw_line(layer, (t_vector2){center.x - x, center.y - y},
			(t_vector2){center.x + x, center.y - y}, color);
		draw_line(layer, (t_vector2){center.x - y, center.y + x},
			(t_vector2){center.x + y, center.y + x}, color);
		draw_line(layer, (t_vector2){center.x - y, center.y - x},
			(t_vector2){center.x + y, center.y - x}, color);
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
