/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   view_init_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmorot <mmorot@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 00:16:06 by mmorot            #+#    #+#             */
/*   Updated: 2025/01/22 00:16:06 by mmorot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "view.h"
#include <math.h>
#include "layer.h"

static void	floor_init(t_game *game, t_floor	*floor)
{
	const double	yaw_rad = (double)game->data->yaw * M_RAD;
	const double	tan_half_fov = tan(((double)FOV / 2.0) * M_RAD);
	const double	pos_z = 0.5 * (OUTPUT_HEIGHT / RATIO);
	const double	posz_div_width = pos_z / (OUTPUT_WIDTH / RATIO);

	floor->height = (OUTPUT_HEIGHT / RATIO);
	floor->width = (OUTPUT_WIDTH / RATIO);
	floor->wall_prop = ((floor->height * 1.0) / (floor->width * 1.0) + STEP);
	floor->texture = layer_stack_get(game->textures, CEILING_TEXTURE);
	floor->width_tex = floor->texture->width;
	floor->player_x = game->data->player.x + 0.5;
	floor->player_y = game->data->player.y + 0.5;
	floor->dir_x = cos(yaw_rad);
	floor->dir_y = sin(yaw_rad);
	floor->plane_x = -floor->dir_y * tan_half_fov;
	floor->plane_y = floor->dir_x * tan_half_fov;
	floor->delta_x = 2 * floor->plane_x * posz_div_width;
	floor->delta_y = 2 * floor->plane_y * posz_div_width;
	floor->base_floor_x = pos_z * (floor->dir_x - floor->plane_x);
	floor->base_floor_y = pos_z * (floor->dir_y - floor->plane_y);
	floor->pos_x = (floor->wall_prop - WALL_HEIGHT) * floor->player_x;
	floor->pos_y = (floor->wall_prop - WALL_HEIGHT) * floor->player_y;
}

void	view_init_bonus(t_game *game, t_game_data *raycast, t_view *view)
{
	t_layer						*group;
	t_layer						*background;
	static const unsigned int	height = (OUTPUT_HEIGHT / RATIO);
	static const int			split = (-(height / 2));

	group = layer_stack_get(game->layers, 1);
	background = layer_group_get(group, 1);
	layer_set_offset(background, 0, split
		+ raycast->pitch * (height / 100));
	view->render = layer_group_get(group, 2);
	view->ray = raycast->ray;
	view->scale_3d = game->scale_3d;
	raycast->center = ((height >> 1) + (raycast->pitch * (height / 100)));
	view->center = raycast->center;
	view->x = 0;
	view->y = 0;
	view->height = height;
	view->width = (OUTPUT_WIDTH / RATIO);
	view->textures = game->textures;
	floor_init(game, &view->floor);
}
