/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook_mouse.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmorot <mmorot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 14:05:25 by mmorot            #+#    #+#             */
/*   Updated: 2025/01/22 17:20:48 by mmorot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"
#include "map.h"

void	hook_mouse(t_game *game)
{
	int	x;
	int	y;

	mlx_mouse_get_pos(game->mlx, game->win, &x, &y);
	game_handle_mouse_move(x, y, game);
}
