#include "types.h"

/*
* Determines the next grid cell
*
* @param map_check    Current map coordinates being checked
* @param side_dist    Distance to next horizontal/vertical grid intersection
* @param delta_dist   Distance between horizontal/vertical grid intersections
* @param step         Direction of movement (-1 or 1) for both axes
*
* @return            0 if horizontal wall hit, 1 if vertical wall hit
*/
int	dda_step(t_vector2 *map_check, t_vector2 *side_dist, t_vector2 delta_dist,
		t_vector2 step)
{
	if (side_dist->x < side_dist->y)
	{
		side_dist->x += delta_dist.x;
		map_check->x += step.x;
		return (0);
	}
	side_dist->y += delta_dist.y;
	map_check->y += step.y;
	return (1);
}
