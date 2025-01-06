#include <math.h>
#include "types.h"

// t_dvector2 dvector2_rotate(t_dvector2 v, int deg)
// {
// 	t_dvector2 new_v = {0, 0};
// 	double rad = deg * M_PI / 180;
// 	new_v.x = v.x * cos(rad) - v.y * sin(rad);
// 	new_v.y = v.x * sin(rad) + v.y * cos(rad);
// 	return (new_v);
// }

t_dvector2	dvector2_rotate(t_dvector2 v, int deg)
{
	static const double	factor = (M_PI / 180);
	const double		rad = deg * factor;
	const double		cosine = cos(rad);
	const double		sine = sin(rad);

	return ((t_dvector2){v.x * cosine - v.y * sine,
		v.x * sine + v.y * cosine});
}

t_dvector2	dvector2_add(t_dvector2 v1, t_dvector2 v2)
{
	return ((t_dvector2){v1.x + v2.x, v1.y + v2.y});
}

t_dvector2	dvector2_sub(t_dvector2 v1, t_dvector2 v2)
{
	return ((t_dvector2){v1.x - v2.x, v1.y - v2.y});
}
