/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmorot <mmorot@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 00:17:11 by mmorot            #+#    #+#             */
/*   Updated: 2025/01/22 00:17:11 by mmorot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"
#include "draw.h"
#include "layer.h"
#include "map.h"

static void	draw_cursor(t_game *game)
{
	t_layer				*group;
	t_layer				*cursor;
	const unsigned int	width = OUTPUT_WIDTH / RATIO;
	const unsigned int	height = OUTPUT_HEIGHT / RATIO;

	group = layer_group_create(CURSOR_SIZE, CURSOR_SIZE, 1);
	if (!group)
	{
		game->is_running = false;
		return ;
	}
	cursor = layer_create(game->mlx, CURSOR_SIZE, CURSOR_SIZE, 1);
	draw_line(cursor, (t_vector2){.x = CURSOR_SIZE
		/ 2, .y = 0}, (t_vector2){.x = CURSOR_SIZE
		/ 2, .y = CURSOR_SIZE}, pixel_create(0, 0, 0, 255));
	draw_line(cursor, (t_vector2){.x = 0, .y = CURSOR_SIZE
		/ 2}, (t_vector2){.x = CURSOR_SIZE, .y = CURSOR_SIZE
		/ 2}, pixel_create(0, 0, 0, 255));
	layer_group_add(group, cursor);
	layer_stack_add(game->layers, group);
	layer_set_offset(group, (width / 2) - (CURSOR_SIZE
			/ 2), (height / 2) - (CURSOR_SIZE / 2));
}

static inline void	center_offset_player_on_map(t_game *game)
{
	t_layer						*group;
	t_layer						*map;
	t_layer						*map_mask;
	static const unsigned int	scale_2d = (SIZE_2D / RATIO);

	group = layer_stack_get(game->layers, 2);
	map = layer_group_get(group, 0);
	map_mask = layer_group_get(group, 1);
	if (!map_mask)
	{
		game->is_running = false;
		return ;
	}
	layer_set_offset(map,
		(layer_get_width(map_mask) >> 1) - (
			game->data->player.x * scale_2d) - (scale_2d >> 1),
		(layer_get_height(map_mask) >> 1) - (
			game->data->player.y * scale_2d) - (scale_2d >> 1)
		);
}

// color => const //valgrind
static void	build_map(t_map *ms, t_game *game, t_layer *map,
	const unsigned int scale_2d)
{
	t_dvector2		pos;

	pos = (t_dvector2){0, 0};
	while (pos.y < ms->height)
	{
		pos.x = 0;
		while (pos.x < ms->width)
		{
			if (ms->tiles[(int)pos.y * ms->width + (int)pos.x] == W)
				draw_rect_fill(map, (t_vector2){pos.x * scale_2d,
					pos.y * scale_2d}, (t_vector2){(pos.x + 1) * scale_2d,
					(pos.y + 1) * scale_2d}, pixel_create(0, 0, 0, 255));
			else if (ms->tiles[(int)pos.y * ms->width + (int)pos.x] == P)
			{
				game->data->player.x = pos.x;
				game->data->player.y = pos.y;
			}
			draw_rect(map, (t_vector2){pos.x * scale_2d, pos.y * scale_2d},
				(t_vector2){(pos.x + 1) * scale_2d, (pos.y + 1) * scale_2d},
				pixel_create(0, 0, 0, 175));
			pos.x++;
		}
		pos.y++;
	}
}

void	map_init(t_map *map_struct, t_game *game)
{
	t_layer				*group;
	t_layer				*map;
	const unsigned int	scale_2d = (SIZE_2D / RATIO);

	group = layer_group_create(((250 * MAP_SIZE_RATIO) / RATIO),
			((250 * MAP_SIZE_RATIO) / RATIO), 2);
	if (!group)
		return ;
	layer_stack_add(game->layers, group);
	map = layer_create(game->mlx, map_struct->width * scale_2d,
			map_struct->height * scale_2d, 0);
	layer_fill(map, pixel_create(125, 125, 125, 200));
	layer_group_add(group, map);
	layer_set_offset(group, MAP_OFFSET, MAP_OFFSET);
	map_draw_init(game, group, map_struct);
	build_map(map_struct, game, map, scale_2d);
	center_offset_player_on_map(game);
	layer_volatile_on(map);
	yaw_init(game);
	if ((OUTPUT_WIDTH / RATIO) < MIN_WIDTH
		|| (OUTPUT_HEIGHT / RATIO) < MIN_WIDTH)
		layer_set_visible(map, false);
	draw_cursor(game);
}
