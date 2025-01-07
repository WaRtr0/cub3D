#include "game.h"
#include <sys/time.h>

double	game_get_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((double)tv.tv_sec + (double)tv.tv_usec / 1000000.0);
}

void	game_calculate_delta_time(t_game *game)
{
	double	current_time;

	if (!game)
		return ;
	current_time = game_get_time();
	game->delta_time = current_time - game->last_frame;
	game->last_frame = current_time;
}
