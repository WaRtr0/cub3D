#include "game.h"
#include "draw.h"
#include "layer.h"
#include "utils.h"
#include "raycast.h"

static void setup_raystep(t_vector2 *ray_dir, t_vector2 *ray_pos, t_vector2 *delta_dist, t_vector2 *step, t_vector2 *side_dist)
{
	delta_dist->x = fabs(1.0 / ray_dir->x);
	delta_dist->y = fabs(1.0 / ray_dir->y);
	if (ray_dir->x < 0)
	{
		step->x = -1;
		side_dist->x = (ray_pos->x - (int)ray_pos->x) * delta_dist->x;
	}
	else
	{
		step->x = 1;
		side_dist->x = ((int)ray_pos->x + 1.0 - ray_pos->x) * delta_dist->x;
	}

	if (ray_dir->y < 0)
	{
		step->y = -1;
		side_dist->y = (ray_pos->y - (int)ray_pos->y) * delta_dist->y;
	}
	else
	{
		step->y = 1;
		side_dist->y = ((int)ray_pos->y + 1.0 - ray_pos->y) * delta_dist->y;
	}
}

/*** Wall hit */
static int	dda_step(t_vector2 *map_check, t_vector2 *side_dist, t_vector2 *delta_dist,
		t_vector2 *step)
{
	if (side_dist->x < side_dist->y)
	{
		side_dist->x += delta_dist->x;
		map_check->x += step->x;
		return (0);
	}
	side_dist->y += delta_dist->y;
	map_check->y += step->y;
	return (1);
}

static int wall_hit(t_vector2 *ray_pos, t_vector2 *ray_dir, 
	t_vector2 *delta_dist, t_vector2 *step, t_vector2 *side_dist,
	t_map *map, t_game *game, int i, double yawRad, double angle_rad)
{
	t_vector2 map_check = {(int)ray_pos->x, (int)ray_pos->y};
    int side;
	t_ray *ray =  ((t_game_data *)game->data)->ray;

	while (1)
	{
		side = dda_step(&map_check, side_dist, delta_dist, step);

		if (map_check.x >= 0 && map_check.x < map->width && 
			map_check.y >= 0 && map_check.y < map->height)
		{
			if (map->tiles[(int)map_check.y * map->width + (int)map_check.x] >= W)
			{
				double wall_dist;
				double wall_x;

				if (side == 0)
				{
					wall_dist = (side_dist->x - delta_dist->x);
					wall_x = ray_pos->y + wall_dist * ray_dir->y;
					wall_x -= floor(wall_x);
					
					if (ray_dir->x > 0)
					{
						ray[i].face = W_FACE;
						ray[i].percent = wall_x * 100;
					}
					else
					{
						ray[i].face = E_FACE;
						ray[i].percent = (1 - wall_x) * 100;
					}
				}
				else
				{
					wall_dist = (side_dist->y - delta_dist->y);
					wall_x = ray_pos->x + wall_dist * ray_dir->x;
					wall_x -= floor(wall_x);
					
					if (ray_dir->y > 0)
					{
						ray[i].face = N_FACE;
						ray[i].percent = (1 - wall_x) * 100;
					}
					else
					{
						ray[i].face = S_FACE;
						ray[i].percent = wall_x * 100;
					}
				}
				if (map->tiles[(int)map_check.y * map->width + (int)map_check.x] == D)
					ray[i].face = D_FACE
						+ animate(game, (int)map_check.y * map->width + (int)map_check.x, 1);
				
				ray[i].distance = wall_dist * cos(angle_rad - yawRad);
				return (0);
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
			return (1);
	}
}

//** rays */
static void rays_hoz(int i, t_vector2 *ray_pos, t_vector2 *ray_dir, t_map *map, t_game *game, double yawRad, double angle_rad)
{
	t_vector2 step;
	t_vector2 side_dist;
	t_vector2 delta_dist;

	t_ray *ray =  ((t_game_data *)game->data)->ray;

	setup_raystep(ray_dir, ray_pos, &delta_dist, &step, &side_dist);

	if (wall_hit(ray_pos, ray_dir, &delta_dist, &step, &side_dist, map, game, i, yawRad, angle_rad))
	{
		ray[i].distance = -1;
		ray[i].percent = 0;
		ray[i].face = 0;
	}
}


void raycast(t_game *game)
{
    t_map *map = game->data->map;
    t_game_data *raycast;
    raycast = game->data;
    raycast->width = WIDTH;
    t_vector2 ray_pos;
    ray_pos.x = game->data->player.x + 0.5;
    ray_pos.y = game->data->player.y + 0.5;
    double screenHalf = (double)raycast->width / 2.0;
    double factor = tan(((double)FOV / 2.0) * (M_PI / 180.0)) / screenHalf;
    double yawRad = (double)game->data->yaw * (M_PI / 180.0);
	int i = 0;
	while (i < raycast->width)
	{
		double cameraX = (double)i - screenHalf;  
		double offsetAngleRad = atan(cameraX * factor);
		double angle_rad = yawRad + offsetAngleRad;
		t_vector2 ray_dir;
	
		ray_dir.x = cos(angle_rad);
		ray_dir.y = sin(angle_rad);
		rays_hoz(i, &ray_pos, &ray_dir, map, game, yawRad, angle_rad);
		angle_rad += (double)FOV / (double)raycast->width * (M_PI / 180.0);
		i++;
	}
}

// void draw_ray(t_vector2 start, t_vector2 map_check, t_vector2 step, int side)
// {
// 	t_vector2 end = {
// 		(map_check.x + (side == 0 ? (step.x < 0 ? 1 : 0) : wall_x)) * SCALE_2D,
// 		(map_check.y + (side == 1 ? (step.y < 0 ? 1 : 0) : wall_x)) * SCALE_2D
// 	};
// 	draw_line(map_layer, start, end, pixel_create(255, 0, 0, 255));
// }