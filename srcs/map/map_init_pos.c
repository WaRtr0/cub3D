/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_init_pos.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmorot <mmorot@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 00:17:13 by mmorot            #+#    #+#             */
/*   Updated: 2025/01/22 00:17:14 by mmorot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"
#include "game.h"
#include "hook.h"
#include "layer.h"
#include "draw.h"
#include "utils.h"

static inline t_triangle_points	init_triangle_points(void)
{
	static const int	size = ((SIZE_2D / RATIO) * HIT_BOX);
	t_triangle_points	points;

	points.center = (t_dvector2){size, size};
	points.pos1 = (t_dvector2){(size >> 2), size};
	points.pos2 = (t_dvector2){size, (size >> 2)};
	points.pos3 = (t_dvector2){(size * 2) - (size >> 2), size};
	return (points);
}

static inline void	apply_rotation(t_dvector2 *pos, t_dvector2 center, int deg)
{
	*pos = dvector2_sub(*pos, center);
	*pos = dvector2_rotate(*pos, deg);
	*pos = dvector2_add(*pos, center);
}

void	yaw_init(t_game *game)
{
	t_triangle_points	points;
	t_layer				*rotate;

	points = init_triangle_points();
	rotate = layer_group_get(layer_stack_get(game->layers, 3), 2);
	layer_fill(rotate, pixel_create(0, 0, 0, 0));
	apply_rotation(&points.pos1, points.center, game->data->yaw);
	apply_rotation(&points.pos2, points.center, game->data->yaw);
	apply_rotation(&points.pos3, points.center, game->data->yaw);
	draw_triangle_fill(rotate,
		(t_triangle_vector){
		(t_vector2){points.pos1.x, points.pos1.y},
		(t_vector2){points.pos2.x, points.pos2.y},
		(t_vector2){points.pos3.x, points.pos3.y}},
		pixel_create(255, 255, 255, 255));
}
