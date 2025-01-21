/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_wall_hit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmorot <mmorot@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 00:16:40 by mmorot            #+#    #+#             */
/*   Updated: 2025/01/22 00:16:40 by mmorot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "layer.h"
#include "raycast.h"

static inline int	dda_step(t_raycast_init *raycast)
{
	if (raycast->side_dist.x < raycast->side_dist.y)
	{
		raycast->side_dist.x += raycast->delta_dist.x;
		raycast->map_check.x += raycast->step.x;
		return (0);
	}
	raycast->side_dist.y += raycast->delta_dist.y;
	raycast->map_check.y += raycast->step.y;
	return (1);
}

inline int	wall_hit(t_raycast_init raycast, t_map *map, t_game *game, int i)
{
	raycast.map_check = (t_vector2){(int)raycast.ray_pos.x,
		(int)raycast.ray_pos.y};
	while (1)
	{
		raycast.side = dda_step(&raycast);
		if (raycast.map_check.x >= 0
			&& raycast.map_check.x < map->width
			&& raycast.map_check.y >= 0 && raycast.map_check.y < map->height)
		{
			if (map->tiles[(int)raycast.map_check.y
					* map->width + (int)raycast.map_check.x] >= W)
			{
				check_side(&raycast, map, game, i);
				return (0);
			}
		}
		else
			return (1);
	}
}
