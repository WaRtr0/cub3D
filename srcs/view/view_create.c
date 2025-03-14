/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   view_create.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmorot <mmorot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 00:16:00 by mmorot            #+#    #+#             */
/*   Updated: 2025/01/22 11:56:50 by mmorot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "view.h"
#include "layer.h"
#include "math.h"

static inline void	texture_pixel_horizontal(t_view *view)
{
	t_pixel	pixel;
	t_layer	*xpm;

	xpm = layer_stack_get(view->textures, view->ray[view->x].face);
	pixel = layer_get_pixel(xpm, floor(view->ray[view->x].percent
				* (double)xpm->width), (view->y
				- (view->center - view->perceived_height))
			/ (view->perceived_height << 1) * xpm->height);
	pixel.a = 255;
	layer_set_pixel(view->render, view->x, view->y, pixel);
}

static inline void	view_init(t_game *game, t_game_data *raycast, t_view *view)
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
	view->textures = game->textures;
}

int	draw_view(t_game *game, t_game_data *raycast)
{
	t_view						view;
	static const unsigned int	height = (OUTPUT_HEIGHT / RATIO);
	static const unsigned int	width = (OUTPUT_WIDTH / RATIO);

	view_init(game, raycast, &view);
	while (view.y < height)
	{
		view.p = view.y - raycast->center;
		view.x = 0;
		while (view.x < width)
		{
			view.perceived_height = view.scale_3d
				/ view.ray[view.x].distance / 2;
			if (view.y >= view.center - view.perceived_height
				&& view.y < raycast->center + view.perceived_height)
				texture_pixel_horizontal(&view);
			view.x++;
		}
		view.y++;
	}
	return (0);
}
