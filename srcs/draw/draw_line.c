#include "draw.h"
#include "layer.h"

void	draw_line(t_layer *layer, t_vector2 start, t_vector2 end, t_pixel color)
{
	t_vector2	delta;
	t_vector2	step;
	t_vector2	current;
	int			longest;
	int			i;

	delta.x = end.x - start.x;
	delta.y = end.y - start.y;
	if (abs((int)delta.x) > abs((int)delta.y))
		longest = abs((int)delta.x);
	else
		longest = abs((int)delta.y);
	step.x = delta.x / (double)longest;
	step.y = delta.y / (double)longest;
	current = start;
	i = 0;
	while (i < longest)
	{
		layer_set_pixel(layer, (int)current.x, (int)current.y, color);
		current.x += step.x;
		current.y += step.y;
		i++;
	}
}
