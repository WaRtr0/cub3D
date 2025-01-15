#include "game.h"
#include "math.h"
#include "../libft/libft.h"

t_game	*game_new(int width, int height, char *title)
{
	t_game	*game;

	game = (t_game *)malloc(sizeof(t_game));
	if (!game)
		return (NULL);
	ft_bzero(game, sizeof(t_game));
	ft_bzero(&game->player_state, sizeof(t_player_state));
	game->data = (t_game_data *)malloc(sizeof(t_game_data));
	if (!game->data)
	{
		free(game);
		return (NULL);
	}
	ft_bzero(game->data, sizeof(t_game_data));
	game->width = width;
	game->height = height;
	game->title = title;
	game->scale_3d = ((((OUTPUT_WIDTH / RATIO) >> 1) / tan(
					(FOV >> 1) * M_PI / 180)) * WALL_HEIGHT);
	if (game_init(game) == 0)
	{
		free(game);
		return (NULL);
	}
	return (game);
}
