
#ifndef RAYCAST_H
# define RAYCAST_H


// # include "game.h"
# include "types.h"



typedef struct s_ray_const
{
	double		screen_half;
	double		factor;
	double		correction;
	double		angle_deg;
}			t_ray_const;
typedef struct s_raycast_init
{
	t_ray		*ray;
	double		offset_angle_rad;
	double		angle_rad;
	double		screen_half;
	double		factor;
	double		yaw_rad;
	double		wall_dist;
	double		wall_x;
	t_ray_const	ray_const;
	int			side;
	t_vector2	ray_pos;
	t_vector2	ray_dir;
	t_vector2	map_check;
	t_vector2	step;
	t_vector2	side_dist;
	t_vector2	delta_dist;
}				t_raycast_init;


void raycast(t_game *game);
int	animate(t_game *game, int pos, int get);
int	wall_hit(t_raycast_init raycast, t_map *map, t_game *game, int i);
// typedef struct s_raycast
// {
// 	t_ray		*ray[1920];
// 	int			width;
// }				t_raycast;

// int				dda_step(t_vector2 *map_check, t_vector2 *side_dist,
// 					t_vector2 delta_dist, t_vector2 step);
// t_raycast		*raycast(t_game *game);
// void			free_raycast(t_raycast *raycast);

#endif