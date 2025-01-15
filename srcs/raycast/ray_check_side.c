#include "raycast.h"
#include "game.h"
#include "utils.h"
#include "draw.h"
#include "layer.h"

static inline void	draw_ray(t_game *game, t_raycast_init *raycast)
{
	t_layer			*map_layer;
	const t_vector2	start = {
		game->data->player.x * SCALE_2D + (SCALE_2D >> 1),
		game->data->player.y * SCALE_2D + (SCALE_2D >> 1)
	};
	t_vector2		end;

	map_layer = layer_group_get(layer_stack_get(game->layers, 2), 0);
	if (raycast->side == 0)
		end.x = (raycast->map_check.x + (raycast->step.x < 0)) * SCALE_2D;
	else
		end.x = (raycast->map_check.x + raycast->wall_x) * SCALE_2D;
	if (raycast->side == 1)
		end.y = (raycast->map_check.y + (raycast->step.y < 0)) * SCALE_2D;
	else
		end.y = (raycast->map_check.y + raycast->wall_x) * SCALE_2D;
	draw_line(map_layer, start, end, pixel_create(255, 0, 0, 255));
}

static inline void	ray_side_zero(t_raycast_init *raycast, t_ray *ray, int i)
{
	raycast->wall_dist = (raycast->side_dist.x - raycast->delta_dist.x);
	raycast->wall_x = raycast->ray_pos.y + raycast->wall_dist
		* raycast->ray_dir.y;
	raycast->wall_x -= floor(raycast->wall_x);
	if (raycast->ray_dir.x > 0)
	{
		ray[i].face = W_FACE;
		ray[i].percent = raycast->wall_x * 100;
	}
	else
	{
		ray[i].face = E_FACE;
		ray[i].percent = (1 - raycast->wall_x) * 100;
	}
}

static inline void	ray_side_one(t_raycast_init *raycast, t_ray *ray, int i)
{
	raycast->wall_dist = (raycast->side_dist.y - raycast->delta_dist.y);
	raycast->wall_x = raycast->ray_pos.x + raycast->wall_dist
		* raycast->ray_dir.x;
	raycast->wall_x -= floor(raycast->wall_x);
	if (raycast->ray_dir.y > 0)
	{
		ray[i].face = N_FACE;
		ray[i].percent = (1 - raycast->wall_x) * 100;
	}
	else
	{
		ray[i].face = S_FACE;
		ray[i].percent = raycast->wall_x * 100;
	}
}

void	check_side(t_raycast_init *raycast,
	t_map *map, t_game *game, int i)
{
	t_ray		*ray;

	ray = raycast->ray;
	if (raycast->side == 0)
		ray_side_zero(raycast, ray, i);
	else
		ray_side_one(raycast, ray, i);
	if (map->tiles[(int)raycast->map_check.y
			* map->width + (int)raycast->map_check.x] >= D)
		ray[i].face = D_FACE
			+ animate(game, (int)raycast->map_check.y
				* map->width + (int)raycast->map_check.x, 1);
	else
		animate(game, -1, 2);
	ray[i].distance = raycast->wall_dist
		* cos(raycast->angle_rad - raycast->yaw_rad);
	if (DEBUG)
		draw_ray(game, raycast);
}
