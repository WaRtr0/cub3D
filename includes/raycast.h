
#ifndef RAYCAST_H
# define RAYCAST_H

# include "types.h"

# define M_PI 3.14159265358979323846
typedef struct s_raycast_data
{
	t_vector2	ray_pos;
	t_vector2	ray_dir;
	t_vector2	delta_dist;
	t_vector2	side_dist;
	t_vector2	step;
	t_vector2	map_check;
	double		wall_dist;
    double        wall_x;
	int			side;
	bool		hit;
}				t_raycast_data;

typedef enum e_face
{
	N_FACE = 1,
	S_FACE = 2,
	E_FACE = 3,
	O_FACE = 4
}				t_face;

typedef struct s_ray
{
	double		distance;
	double		percent;
	int			face;
}				t_ray;


typedef struct s_raycast
{
	t_ray		*ray[1920];
	int			width;
}				t_raycast;

// int				dda_step(t_vector2 *map_check, t_vector2 *side_dist,
// 					t_vector2 delta_dist, t_vector2 step);
// t_raycast		*raycast(t_game *game);
// void			free_raycast(t_raycast *raycast);

#endif