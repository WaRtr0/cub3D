#include "layer.h"

void	draw_rect(t_layer *layer, t_vector2 start, t_vector2 end, t_pixel color)
{
	int	x;
	int	y;

	x = start.x;
	while (x <= end.x)
	{
		layer_set_pixel(layer, x, start.y, color);
		layer_set_pixel(layer, x, end.y, color);
		x++;
	}
	y = start.y;
	while (y <= end.y)
	{
		layer_set_pixel(layer, start.x, y, color);
		layer_set_pixel(layer, end.x, y, color);
		y++;
	}
}
