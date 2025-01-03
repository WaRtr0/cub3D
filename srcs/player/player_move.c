#include "game.h"
#include "cub.h"
#include "layer.h"

static inline void center_offset_player_on_map(t_game *game)
{
	t_layer *group = layer_stack_get(game->layers, 2);
    t_layer *map = layer_group_get(group, 0);
    t_layer *map_mask = layer_group_get(group, 1);
    
	layer_set_offset(map,
		(map_mask->width >> 1) - (game->data->player.x * SCALE_2D) - (SCALE_2D >> 1) + map_mask->offset_x,
		(map_mask->height >> 1) - (game->data->player.y * SCALE_2D) - (SCALE_2D >> 1) + map_mask->offset_y
    );
}

static inline void move_along(t_game *game, int side, double new_x, double new_y)
{
	if (side == 0 && new_y < game->data->player.y + 0.5)
		game->data->player.y = new_y - 0.5;
	else if (side == 1 && new_x > game->data->player.x + 0.5)
		game->data->player.x = new_x - 0.5;
	else if (side == 2 && new_y > game->data->player.y + 0.5)
		game->data->player.y = new_y - 0.5;
	else if (side == 3 && new_x < game->data->player.x + 0.5)
		game->data->player.x = new_x - 0.5;
}

void	player_move(t_game *game, int dir)
{
	int			i;
    t_map		*map = game->data->map;
	int			check_tile;

    double	move_x = sin((game->data->yaw) * M_PI / 180) * (STEP + game->player_state.running * STEP);
    double	move_y = -cos((game->data->yaw) * M_PI / 180) * (STEP + game->player_state.running * STEP);

    // Calcul de la nouvelle position potentielle
    double new_x = game->data->player.x + (move_x * dir) + 0.5;
    double new_y = game->data->player.y + (move_y * dir) + 0.5;
    
    // Points de collision (centre + diagonales)
    int check_points[][2] = {
        {0, -1},     // Haut
		{1, 0},     // Droite
		{0, 1},    // Bas
		{-1, 0}     // Gauche
    };
	// Vérification des collisions
	check_tile = map->tiles[(int)new_y * map->width + (int)new_x];
	if (check_tile == W || check_tile == D)
		return ;
	i = 0;
	while (i < 4)
	{
		double check_x = new_x + (check_points[i][0] * HIT_BOX);
		double check_y = new_y + (check_points[i][1] * HIT_BOX);
		// Vérification des limites de la carte
		if (check_x >= 0 && check_x < map->width && 
			check_y >= 0 && check_y < map->height)
		{
			// Vérification des collisions avec les murs
			check_tile = map->tiles[(int)check_y * map->width + (int)check_x];
			if (check_tile != W && check_tile != D)
				move_along(game, i, new_x, new_y);
		}
		i++;
	}
	if (i == 4)
    	center_offset_player_on_map(game);
}
