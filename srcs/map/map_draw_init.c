/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_draw_init.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmorot <mmorot@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 00:17:16 by mmorot            #+#    #+#             */
/*   Updated: 2025/01/22 00:17:17 by mmorot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"
#include "draw.h"
#include "layer.h"

static void	draw_all_circle(t_layer *circle_map, t_layer *map_mask)
{
	const unsigned int	half_map = ((250 * MAP_SIZE_RATIO) / RATIO) >> 1;

	draw_circle_fill(map_mask, (t_vector2){half_map, half_map},
		half_map, pixel_create(0, 0, 0, 255));
	draw_circle(circle_map, (t_vector2){half_map, half_map},
		half_map - 5, pixel_create(255, 255, 0, 255));
	draw_circle(circle_map, (t_vector2){half_map, half_map},
		half_map - 4, pixel_create(200, 200, 0, 255));
	draw_circle(circle_map, (t_vector2){half_map, half_map},
		half_map - 3, pixel_create(150, 150, 0, 255));
	draw_circle(circle_map, (t_vector2){half_map, half_map},
		half_map - 2, pixel_create(150, 150, 0, 255));
	draw_circle(circle_map, (t_vector2){half_map, half_map},
		half_map - 1, pixel_create(100, 100, 0, 255));
	draw_circle(circle_map, (t_vector2){half_map, half_map},
		half_map - 0, pixel_create(50, 50, 0, 255));
}

static t_layer	*add_player(t_game *game)
{
	t_layer				*player;
	t_layer				*rotate;
	t_layer				*cursor;
	const unsigned int	scale_2d = (SIZE_2D / RATIO);

	cursor = layer_group_create(scale_2d * HIT_BOX * 2,
			scale_2d * HIT_BOX * 2, 3);
	if (!cursor)
		return (NULL);
	player = layer_create(game->mlx, scale_2d * HIT_BOX * 2,
			scale_2d * HIT_BOX * 2, 1);
	rotate = layer_create(game->mlx, scale_2d * HIT_BOX * 2,
			scale_2d * HIT_BOX * 2, 2);
	layer_group_add(cursor, player);
	layer_group_add(cursor, rotate);
	layer_stack_add(game->layers, cursor);
	draw_circle_fill(player, (t_vector2){scale_2d * HIT_BOX,
		scale_2d * HIT_BOX}, scale_2d * HIT_BOX,
		pixel_create(255, 0, 0, 255));
	if ((OUTPUT_WIDTH / RATIO) < 550 || (OUTPUT_HEIGHT / RATIO) < 550)
		(layer_set_visible(player, false), layer_set_visible(rotate, false));
	return (cursor);
}

static void	check(t_layer *circle_map, t_layer *map_mask)
{
	if ((OUTPUT_WIDTH / RATIO) < MIN_WIDTH
		|| (OUTPUT_HEIGHT / RATIO) < MIN_WIDTH)
	{
		layer_set_visible(circle_map, false);
		layer_set_visible(map_mask, false);
	}
}

void	map_draw_init(t_game *game, t_layer *group, t_map *map_struct)
{
	t_layer	*mpm;
	t_layer	*circle_map;
	t_layer	*raycast_debug;
	t_layer	*cursor;

	raycast_debug = layer_create(game->mlx,
			map_struct->width * (SIZE_2D / RATIO),
			map_struct->height * (SIZE_2D / RATIO), 5);
	mpm = layer_create(game->mlx, ((250 * MAP_SIZE_RATIO) / RATIO),
			((250 * MAP_SIZE_RATIO) / RATIO), 1);
	layer_set_mask(mpm, true);
	circle_map = layer_create(game->mlx, ((250 * MAP_SIZE_RATIO) / RATIO),
			((250 * MAP_SIZE_RATIO) / RATIO), 3);
	layer_group_add(group, circle_map);
	layer_group_add(group, mpm);
	layer_group_add(group, raycast_debug);
	draw_all_circle(circle_map, mpm);
	cursor = add_player(game);
	layer_set_offset(cursor,
		(layer_get_width(mpm) / 2) - (SIZE_2D / RATIO) * HIT_BOX + MAP_OFFSET,
		(layer_get_width(mpm) / 2) - (SIZE_2D / RATIO) * HIT_BOX + MAP_OFFSET);
	check(circle_map, mpm);
}
