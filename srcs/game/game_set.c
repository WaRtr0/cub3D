/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_set.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmorot <mmorot@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 00:18:54 by mmorot            #+#    #+#             */
/*   Updated: 2025/01/22 00:18:54 by mmorot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"

void	game_set_update_callback(t_game *game, void (*update)(t_game *))
{
	if (game)
		game->update_callback = (void *)update;
}

void	game_set_hook_press(t_game *game, void (*hook)(int, t_game *))
{
	if (game)
		game->hook_callback = (void *)hook;
}

void	game_set_hook_release(t_game *game, void (*hook)(int, t_game *))
{
	if (game)
		game->hook_release = (void *)hook;
}

void	game_set_hook_mouse_move(t_game *game, void (*hook)(int, int, t_game *))
{
	if (game)
		game->hook_mouse_move = (void *)hook;
}

void	game_set_hook_mouse_press(t_game *game, void (*hook)
	(int, int, t_game *))
{
	if (game)
		game->hook_mouse_press = (void *)hook;
}
