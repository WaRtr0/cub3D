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
