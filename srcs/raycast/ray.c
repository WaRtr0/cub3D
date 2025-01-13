#include "game.h"
#include "draw.h"
#include "layer.h"
#include "utils.h"
#include "raycast.h"





//** rays */

static inline void	setup_raystep(t_raycast_init *r)
{
	r->delta_dist.x = fabs(1.0 / r->ray_dir.x);
	r->delta_dist.y = fabs(1.0 / r->ray_dir.y);
	if (r->ray_dir.x < 0)
	{
		r->step.x = -1;
		r->side_dist.x = (r->ray_pos.x - (int)r->ray_pos.x) * r->delta_dist.x;
	}
	else
	{
		r->step.x = 1;
		r->side_dist.x = ((int)r->ray_pos.x
				+ 1.0 - r->ray_pos.x) * r->delta_dist.x;
	}
	if (r->ray_dir.y < 0)
	{
		r->step.y = -1;
		r->side_dist.y = (r->ray_pos.y - (int)r->ray_pos.y) * r->delta_dist.y;
	}
	else
	{
		r->step.y = 1;
		r->side_dist.y = ((int)r->ray_pos.y
				+ 1.0 - r->ray_pos.y) * r->delta_dist.y;
	}
}

static inline void	rays(int i, t_map *map,
	t_game *game, t_raycast_init *raycast)
{
	t_ray	*ray;

	ray = raycast->ray;
	setup_raystep(raycast);

	if (wall_hit(*raycast, map, game, i))
	{
		ray[i].distance = -1;
		ray[i].percent = 0;
		ray[i].face = 0;
	}
}

static inline t_ray_const	ray_const(t_game_data *raycast)
{
	static t_ray_const	cached_ray_const;
	static unsigned int	i = 0;
	t_ray				*ray;

	if (!i)
	{
		cached_ray_const.screen_half = (double)WIDTH / 2.0;
		cached_ray_const.angle_deg = (M_PI / 180.0);
		cached_ray_const.factor = tan(((double)FOV / 2.0)
				* cached_ray_const.angle_deg) / cached_ray_const.screen_half ;
		ray = raycast->ray;
		while (i < WIDTH)
		{
			ray[i].offset_angle_rad = atan(
					(i - cached_ray_const.screen_half)
					* cached_ray_const.factor);
			i++;
		}
	}
	return (cached_ray_const);
}


void	raycast(t_game *game)
{
	t_map					*map;
	static t_raycast_init	raycast_init;
	unsigned int			i;

	map = game->data->map;
	raycast_init.ray = ((t_game_data *)game->data)->ray;
	raycast_init.ray_const = ray_const(game->data);
	raycast_init.ray_pos.x = game->data->player.x + 0.5;
	raycast_init.ray_pos.y = game->data->player.y + 0.5;
	raycast_init.yaw_rad = (double)game->data->yaw
		* raycast_init.ray_const.angle_deg;
	i = 0;
	while (i < WIDTH)
	{
		raycast_init.angle_rad = raycast_init.yaw_rad
			+ raycast_init.ray[i].offset_angle_rad;
		raycast_init.ray_dir.x = cos(raycast_init.angle_rad);
		raycast_init.ray_dir.y = sin(raycast_init.angle_rad);
		rays(i, map, game, &raycast_init);
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