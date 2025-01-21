/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmorot <mmorot@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 00:16:11 by mmorot            #+#    #+#             */
/*   Updated: 2025/01/22 00:16:11 by mmorot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
	const double		rad = (deg + 90) * M_RAD;
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
