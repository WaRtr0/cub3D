/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   animation.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: garivo <garivo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 17:26:44 by garivo            #+#    #+#             */
/*   Updated: 2025/01/07 19:27:43 by garivo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"
#include "utils.h"

int	get_frame()
{
	static long long		timestamp;
	long long		time;
	long long		diff;

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

int	animate(t_game *game, int pos, int get)
{
	static t_door	door = {-1, 0};
	long long		time;
	long long		diff;

	time = current_time();
	if (door.pos != pos && get)
		return (get_frame());
	if (door.pos == -1 && !get)
	{
		door.pos = pos;
		door.timestamp = time;
	}
	if (door.pos == pos && get)
	{
		diff = time - door.timestamp;
		if (diff <= 1500)
			return ((get_frame() * diff / 100) / 4 % 36);
		else if (diff <= 1650)
			return (36);
		else
		{
			game->data->map->tiles[pos] = E;
			door.pos = -1;
			return (0);
		}
	}
	return (0);
}
