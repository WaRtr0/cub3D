#include "cub.h"
#include "game.h"
#include "types.h"
#include "draw.h"
#include "layer.h"
#include "math.h"
#include "utils.h"

void debug_print_raycast(t_game_data *raycast)
{
	for (int i = 0; i < raycast->width; i++)
	{
		printf("Ray %d: distance: %f, percent: %f, face: %d\n", i, raycast->ray[i].distance, raycast->ray[i].percent, raycast->ray[i].face);
	}
}

int	animate(t_game *game, int pos, int get)
{
	static t_door	door = {-1, 0};
	long long		time;
	long long		diff;

	time = current_time();
	if (door.pos == -1 && !get)
	{
		door.pos = pos;
		door.timestamp = time;
	}
	if (door.pos == pos && get)
	{
		diff = time - door.timestamp;
		if (diff <= 500)
			return (0);
		else if (diff <= 1000)
			return (1);
		else
		{
			game->data->map->tiles[pos] = E;
			door.pos = -1;
			return (0);
		}
	}
	return (0);
}

void raycast(t_game *game)
{
   t_layer *group = layer_stack_get(game->layers, 2);
    
    
    
    
    t_map *map = game->data->map;
    t_game_data *raycast;

    raycast = game->data;
    raycast->width = WIDTH;
    // raycast->ray = malloc(sizeof(t_ray*) * raycast->width);
    
    // double ray_angle = (game->data->yaw - 90 - FOV/2.0)
    // + ((double)i * FOV / raycast->width);
    t_vector2 ray_pos;
    double sub_angle = FOV / (double)raycast->width;
    double angle = game->data->yaw - 90 - (FOV >> 1);
    ray_pos.x = game->data->player.x + 0.5;
    ray_pos.y = game->data->player.y + 0.5;
    for (int i = 0; i < raycast->width; i++)
    {
        
        t_vector2 ray_dir;
        t_vector2 delta_dist;
        t_vector2 step;
        t_vector2 side_dist;
        bool hit = false;
        int side;
        
        // double ray_angle = angle + (double)i * sub_angle;
        // double ray_angle = (i - (raycast->width / 2)) * ((1. / raycast->width) * (game->data->yaw - 90));
        double ray_angle = angle + ((double)i * sub_angle);
        double angle_rad = ray_angle * (M_PI / 180.0);
        
        
        
        ray_dir.x = cos(angle_rad);
        ray_dir.y = sin(angle_rad);
        
        delta_dist.x = (ray_dir.x == 0) ? 1e30 : fabs(1.0 / ray_dir.x);
        delta_dist.y = (ray_dir.y == 0) ? 1e30 : fabs(1.0 / ray_dir.y);
        
        if (ray_dir.x < 0)
        {
            step.x = -1;
            side_dist.x = (ray_pos.x - (int)ray_pos.x) * delta_dist.x;
        }
        else
        {
            step.x = 1;
            side_dist.x = ((int)ray_pos.x + 1.0 - ray_pos.x) * delta_dist.x;
        }
        if (ray_dir.y < 0)
        {
            step.y = -1;
            side_dist.y = (ray_pos.y - (int)ray_pos.y) * delta_dist.y;
        }
        else
        {
            step.y = 1;
            side_dist.y = ((int)ray_pos.y + 1.0 - ray_pos.y) * delta_dist.y;
        }
        
        t_vector2 map_check = {(int)ray_pos.x, (int)ray_pos.y};
        // raycast->ray[i] = malloc(sizeof(t_ray));
        
        while (!hit)
        {
            if (side_dist.x < side_dist.y)
            {
                side_dist.x += delta_dist.x;
                map_check.x += step.x;
                side = 0;
            }
            else
            {
                side_dist.y += delta_dist.y;
                map_check.y += step.y;
                side = 1;
            }
            
            if (map_check.x >= 0 && map_check.x < map->width && 
                map_check.y >= 0 && map_check.y < map->height)
            {
                if (map->tiles[(int)map_check.y * map->width + (int)map_check.x] >= W)
                {
                    hit = true;
                    double wall_dist;
                    double wall_x;

                    if (side == 0)
                    {
                        wall_dist = (side_dist.x - delta_dist.x);
                        wall_x = ray_pos.y + wall_dist * ray_dir.y;
                        wall_x -= floor(wall_x);
                        
                        if (ray_dir.x > 0)
                        {
                            raycast->ray[i].face = W_FACE;
                            raycast->ray[i].percent = wall_x * 100;
                        }
                        else
                        {
                            raycast->ray[i].face = E_FACE;
                            raycast->ray[i].percent = (1 - wall_x) * 100;
                        }
                    }
                    else
                    {
                        wall_dist = (side_dist.y - delta_dist.y);
                        wall_x = ray_pos.x + wall_dist * ray_dir.x;
                        wall_x -= floor(wall_x);
                        
                        if (ray_dir.y > 0)
                        {
                            raycast->ray[i].face = N_FACE;
                            raycast->ray[i].percent = (1 - wall_x) * 100;
                        }
                        else
                        {
                            raycast->ray[i].face = S_FACE;
                            raycast->ray[i].percent = wall_x * 100;
                        }
                    }
					if (map->tiles[(int)map_check.y * map->width + (int)map_check.x] == D)
						raycast->ray[i].face = D_FACE
							+ animate(game, (int)map_check.y * map->width + (int)map_check.x, 1);
                    
                    // fish eye correction
                    raycast->ray[i].distance = wall_dist * cos((ray_angle - raycast->yaw + 90) * M_PI / 180.0);
                    
                    //  t_layer *map_layer = layer_group_get(group, 0);
                   
                    // t_vector2 start = {
                    //     game->data->player.x * SCALE_2D + SCALE_2D/2,
                    //     game->data->player.y * SCALE_2D + SCALE_2D/2
                    // };
                    // t_vector2 end = {
                    //     (map_check.x + (side == 0 ? (step.x < 0 ? 1 : 0) : wall_x)) * SCALE_2D,
                    //     (map_check.y + (side == 1 ? (step.y < 0 ? 1 : 0) : wall_x)) * SCALE_2D
                    // };
                    // draw_line(map_layer, start, end, pixel_create(255, 0, 0, 255));
                }
            }
            else
                break;
        }
        if (!hit)
        {
            raycast->ray[i].distance = -1;
            raycast->ray[i].percent = 0;
            raycast->ray[i].face = 0;
        }
    }
    t_layer *map_layer = layer_group_get(group, 0);
    draw_circle_fill(map_layer, (t_vector2){game->data->player.x * SCALE_2D + SCALE_2D/2, game->data->player.y * SCALE_2D + SCALE_2D/2}, 5, pixel_create(255, 0, 0, 255));
    // debug_print_raycast(raycast);
}