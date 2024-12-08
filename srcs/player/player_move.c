#include "game.h"
#include "cub.h"
#include "layer.h"

static inline void center_offset_player_on_map(t_game *game)
{
    t_layer *map = layer_stack_get(game->layers, 100);
    t_layer *map_mask = layer_stack_get(game->layers, 101);
    
	layer_set_offset(map,
		map_mask->width/2 - (game->data->player.x * SCALE_2D) - SCALE_2D/2 + map_mask->offset_x,
		map_mask->height/2 - (game->data->player.y * SCALE_2D) - SCALE_2D/2 + map_mask->offset_y
    );
}

void player_move(t_game *game, int dir)
{
    t_map *map = game->data->map;
    double move_x = sin((game->data->yaw) * M_PI / 180) * SPEED;
    double move_y = -cos((game->data->yaw) * M_PI / 180) * SPEED;
    
    t_vector2 pos = {
        game->data->player.x,
        game->data->player.y
    };
    
    t_vector2 ray_dir = {move_x * dir, move_y * dir};
    t_vector2 delta_dist = {
        (ray_dir.x == 0) ? 1e30 : fabs(1.0 / ray_dir.x),
        (ray_dir.y == 0) ? 1e30 : fabs(1.0 / ray_dir.y)
    };
    
    t_vector2 step;
    t_vector2 side_dist;
    
    // Calcul des distances aux prochains bords de case (comme dans le raycast)
    if (ray_dir.x < 0)
    {
        step.x = -1;
        side_dist.x = (pos.x - (int)pos.x) * delta_dist.x;
    }
    else
    {
        step.x = 1;
        side_dist.x = ((int)pos.x + 1.0 - pos.x) * delta_dist.x;
    }
    
    if (ray_dir.y < 0)
    {
        step.y = -1;
        side_dist.y = (pos.y - (int)pos.y) * delta_dist.y;
    }
    else
    {
        step.y = 1;
        side_dist.y = ((int)pos.y + 1.0 - pos.y) * delta_dist.y;
    }
    
    t_vector2 map_check = {(int)pos.x, (int)pos.y};
    double distance = 0;
    int side;
    
    // Vérification de collision comme le raycast
    while (distance < HIT_BOX + SPEED)
    {
        if (side_dist.x < side_dist.y)
        {
            distance = side_dist.x;
            side_dist.x += delta_dist.x;
            map_check.x += step.x;
            side = 0;
        }
        else
        {
            distance = side_dist.y;
            side_dist.y += delta_dist.y;
            map_check.y += step.y;
            side = 1;
        }
        
        // Vérification des limites et collision
        if (map_check.x >= 0 && map_check.x < map->width && 
            map_check.y >= 0 && map_check.y < map->height)
        {
            if (map->tiles[(int)map_check.y * map->width + (int)map_check.x] == W)
            {
                return; // Collision détectée
            }
        }
        else
            return; // Hors limites
    }
    
    // Si on arrive ici, pas de collision détectée
    game->data->player.x += ray_dir.x;
    game->data->player.y += ray_dir.y;
    center_offset_player_on_map(game);
}

// void player_move(t_game *game, int dir)
// {
//     t_map *map = game->data->map;
//     double move_x = sin((game->data->yaw) * M_PI / 180) * SPEED;
//     double move_y = -cos((game->data->yaw) * M_PI / 180) * SPEED;
    
//     // Calcul de la nouvelle position potentielle
//     double new_x = game->data->player.x + (move_x * dir);
//     double new_y = game->data->player.y + (move_y * dir);
    
//     // Points de collision (centre + diagonales)
//     int check_points[][2] = {
//         {0, 0},     // Centre
//         {-1, -1},   // Haut gauche
//         {1, -1},    // Haut droite
//         {-1, 1},    // Bas gauche
//         {1, 1}      // Bas droite
//     };
    
//     // Vérification des collisions
//     bool collision = false;
//     for (int i = 0; i < 5; i++)
//     {
//         double check_x = new_x + (check_points[i][0] * HIT_BOX);
//         double check_y = new_y + (check_points[i][1] * HIT_BOX);
        
//         // Vérification des limites de la carte
//         if (check_x < 0 || check_x >= map->width || 
//             check_y < 0 || check_y >= map->height)
//         {
//             collision = true;
//             break;
//         }
        
//         // Vérification des collisions avec les murs
//         int map_x = (int)check_x;
//         int map_y = (int)check_y;
        
//         if (map->tiles[map_y * map->width + map_x] == W)
//         {
//             collision = true;
//             break;
//         }
//     }
    
//     // Si pas de collision, appliquer le mouvement
//     if (!collision)
//     {
//         game->data->player.x = new_x;
//         game->data->player.y = new_y;
//         center_offset_player_on_map(game);
//     }
// }