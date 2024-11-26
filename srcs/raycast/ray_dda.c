#include "types.h"

int	dda_step(t_vector2 *map_check, t_vector2 *side_dist, t_vector2 delta_dist,
		t_vector2 step)
{
	int side;

	if (side_dist->x < side_dist->y)
	{
		side_dist->x += delta_dist.x;
		map_check->x += step.x;
		side = 0;
	}
	else
	{
		side_dist->y += delta_dist.y;
		map_check->y += step.y;
		side = 1;
	}
	return (side);
}
