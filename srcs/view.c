/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   view.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: garivo <garivo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 15:54:01 by garivo            #+#    #+#             */
/*   Updated: 2024/11/19 13:20:51 by garivo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "view.h"

void	layer_split(t_layer *layer, t_pixel color1, t_pixel color2)
{
    int x;
    int y;

	y = 0;
	while (y < layer->height / 2)
	{
		x = 0;
		while (x < layer->width)
			layer_set_pixel(layer, x++, y, color1);
		y++;
	}
	while (y < layer->height)
	{
		x = 0;
		while (x < layer->width)
			layer_set_pixel(layer, x++, y, color2);
		y++;
	}
}

t_view	get_view(t_game *game)
{
	t_view view;

	view.center = 0;
	view.width = game->width;
	view.height = game->height;
	view.wall_height = 400;

	return (view);
}

int	draw_view(t_game *game, t_view view)
{
	t_layer *render;
	int		center;
	int		x;
	int		y;
	int		perceived_height;

	double distance_table[] = {
    5.0, 5.1, 5.2, 5.3, 5.4, 5.5, 5.6, 5.7, 5.8, 5.9, 
    6.0, 6.1, 6.2, 6.3, 6.4, 6.5, 6.6, 6.7, 6.8, 6.9,
    7.0, 7.1, 7.2, 7.3, 7.4, 7.5, 7.6, 7.7, 7.8, 7.9,
    8.0, 8.1, 8.2, 8.3, 8.4, 8.5, 8.6, 8.7, 8.8, 8.9,
    9.0, 9.1, 9.2, 9.3, 9.4, 9.5, 9.6, 9.7, 9.8, 9.9,
    10.0, 10.1, 10.2, 10.3, 10.4, 10.5, 10.6, 10.7, 10.8, 10.9,
    11.0, 11.1, 11.2, 11.3, 11.4, 11.5, 11.6, 11.7, 11.8, 11.9,
    12.0, 12.1, 12.2, 12.3, 12.4, 12.5, 12.6, 12.7, 12.8, 12.9,
    13.0, 13.1, 13.2, 13.3, 13.4, 13.5, 13.6, 13.7, 13.8, 13.9,
    14.0, 14.1, 14.2, 14.3, 14.4, 14.5, 14.6, 14.7, 14.8, 14.9,
	};
	view.distances = distance_table;

	render = layer_create(game->mlx, view.width, view.height, 0);
	center = view.height / 2 + view.center;
	x = 0;
	while (x < 500)
	{
		perceived_height = (int)(view.wall_height / view.distances[x]);
		y = center - perceived_height / 2;
		while (y < center + perceived_height / 2)
			layer_set_pixel(render, x, y++, pixel_create(255, 0, 0, 255));
		x++;
	}
	layer_stack_add(game->layers, render);
	return (0);
}

int	create_view(t_game *game)
{
	t_layer	*background;
	t_view	view;
	
	t_layer *stupid_test = layer_create(game->mlx, game->width, game->height, 0);
	layer_stack_add(game->layers, stupid_test);
	
	background = layer_create(game->mlx, game->width, game->height, 0);
	layer_split(background, pixel_create(45, 0, 190, 255), pixel_create(40, 40, 40, 255));
	layer_stack_add(game->layers, background);

	draw_view(game, get_view(game));

	return (0);
}
