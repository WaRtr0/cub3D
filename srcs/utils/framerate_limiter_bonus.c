/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   framerate_limiter_bonus.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: garivo <garivo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 16:51:54 by garivo            #+#    #+#             */
/*   Updated: 2025/01/20 17:12:18 by garivo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

long long	current_time(void);

int	frame_limit(void)
{
	static long long	lastframe = 0;
	long long			time;

	time = current_time();
	if (lastframe == 0)
		lastframe = time;
	if (time - lastframe >= 1000 / FRAME_RATE)
	{
		lastframe = time;
		return (1);
	}
	return (0);
}
