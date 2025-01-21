/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook_press.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmorot <mmorot@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 00:18:44 by mmorot            #+#    #+#             */
/*   Updated: 2025/01/22 00:18:45 by mmorot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"
#include "hook.h"
#include "player.h"
#include "layer.h"
#include "map.h"

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
		(map_mask->width >> 1) - (
			game->data->player.x * scale_2d) - (scale_2d >> 1),
		(map_mask->height >> 1) - (
			game->data->player.y * scale_2d) - (scale_2d >> 1)
		);
}

void	hook_press_dir(int keycode, t_game *game)
{
	if (keycode == KEY_W)
		game->player_state.move_dir[0] = 1;
	if (keycode == KEY_S)
		game->player_state.move_dir[1] = 1;
	if (keycode == KEY_A)
		game->player_state.move_dir[2] = 1;
	if (keycode == KEY_D)
		game->player_state.move_dir[3] = 1;
}

void	hook_press(int keycode, t_game *game)
{
	if (keycode == KEY_NUM_6)
		game->data->player.x += 1;
	if (keycode == KEY_NUM_4)
		game->data->player.x -= 1;
	if (keycode == KEY_NUM_8)
		game->data->player.y -= 1;
	if (keycode == KEY_NUM_2)
		game->data->player.y += 1;
	if ((keycode >= KEY_NUM_4) | (keycode <= KEY_NUM_2))
		center_offset_player_on_map(game);
	hook_press_dir(keycode, game);
	if (keycode == KEY_SPACE)
		interact_door(game, 1);
	if (keycode == KEY_LEFT)
		game->player_state.key_yaw = -1;
	if (keycode == KEY_RIGHT)
		game->player_state.key_yaw = 1;
	if (keycode == KEY_SHIFT)
		game->player_state.running = 1;
	if (keycode == KEY_ESC)
		game_handle_close(game);
}
