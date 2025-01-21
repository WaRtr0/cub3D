/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_animation_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmorot <mmorot@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 17:26:44 by garivo            #+#    #+#             */
/*   Updated: 2025/01/22 00:16:48 by mmorot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"
#include "utils.h"

long long	current_time(void);

int	get_frame(void)
{
	static long long		timestamp;
	long long				time;
	long long				diff;

	if (timestamp == 0)
		timestamp = current_time();
	time = current_time();
	diff = time - timestamp;
	if (diff >= 1800)
	{
		timestamp = time;
		return (0);
	}
	else
		return (diff / 50);
}

int	open_door(t_game *game, int pos, int get, long long time)
{
	static t_door	door = {-1, 0, 0};
	long long		diff;

	time = current_time();
	if (door.pos != -1 && time - door.timestamp > 1550)
	{
		game->data->map->tiles[door.pos] = H;
		door.pos = -1;
	}
	if (door.pos != pos && get == 1)
		return (get_frame());
	if (door.pos == -1 && !get)
	{
		door.pos = pos;
		door.timestamp = time;
		door.start = get_frame();
	}
	if (door.pos == pos && get == 1)
	{
		diff = time - door.timestamp;
		if (diff <= 1400)
			return ((door.start + diff / 50 + diff * diff / 2 / 5000) % 36);
		return (36);
	}
	return (0);
}

int	close_door(t_game *game, int pos, int get)
{
	static t_door	door = {-1, 0, 0};
	long long		time;
	long long		diff;

	time = current_time();
	if (door.pos != -1 && time - door.timestamp > 750)
	{
		game->data->map->tiles[door.pos] = D;
		door.pos = -1;
	}
	if (door.pos == -1 && !get)
	{
		game->data->map->tiles[pos] = C;
		door.pos = pos;
		door.timestamp = time;
		door.start = get_frame();
	}
	if (door.pos == pos && get == 1)
	{
		diff = time - door.timestamp;
		if ((diff >= 150 && diff <= 300) || (diff >= 450 && diff <= 600))
			return (get_frame());
		return (36);
	}
	return (0);
}

int	animate(t_game *game, int pos, int get)
{
	if (pos >= 0 && game->data->map->tiles[pos] == D)
		return (open_door(game, pos, get, 0));
	else if (pos >= 0 && (game->data->map->tiles[pos] == C
			|| game->data->map->tiles[pos] == H))
		return (close_door(game, pos, get));
	open_door(game, pos, get, 0);
	close_door(game, pos, get);
	return (0);
}
