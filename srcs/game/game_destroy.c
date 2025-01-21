/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_destroy.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmorot <mmorot@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 00:19:08 by mmorot            #+#    #+#             */
/*   Updated: 2025/01/22 00:19:08 by mmorot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"
#include "layer.h"

void	game_destroy(t_game *game)
{
	if (!game)
		return ;
	if (game->layers)
		layer_stack_destroy(game->mlx, game->layers);
	if (game->textures)
		layer_stack_destroy(game->mlx, game->textures);
	if (game->data->map)
	{
		if (game->data->map->tiles)
			free(game->data->map->tiles);
		free(game->data->map);
	}
	if (game->data)
		free(game->data);
	if (game->win)
		mlx_destroy_window(game->mlx, game->win);
	if (game->mlx)
	{
		mlx_destroy_display(game->mlx);
		free(game->mlx);
	}
	free(game);
}
