#ifndef TYPES_H
# define TYPES_H

# define LAYER_STACK_CAPACITY 256

# include <stdbool.h>
# include "raycast.h"
# include "types.h"

typedef enum e_map_tile
{
	E = 0, // empty
	W = 1, // wall
	P = 2, // player
	D = 3 // door
} t_map_tile;

typedef struct s_vector2
{
	double			x;
	double			y;
}					t_vector2;

typedef struct s_dvector2
{
	int	x;
	int	y;
}					t_dvector2;	

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

typedef struct s_map {
	t_map_tile	*tiles;
	int			width;
	int			height;
} t_map;

typedef struct s_pixel
{
	unsigned int	r;
	unsigned int	g;
	unsigned int	b;
	unsigned int	a;
}					t_pixel;

typedef struct s_layer
{
    void            *img;
    unsigned int    *data;
    int             width;
    int             height;
    int             offset_x;
    int             offset_y;
    int             visible;
    int             z_index;
    int             bits_per_pixel;
    int             line_length;
    int             endian;
	bool			mask;
    t_pixel         clear_color;
} t_layer;

// typedef struct s_render_data
// {
//     unsigned int    *output;
//     unsigned int    *layer;
//     int             width;
//     int             height;
//     int             offset_x;
//     int             offset_y;
// }   t_render_data;

typedef struct s_layer_stack
{
	t_layer			*layers[LAYER_STACK_CAPACITY];
	t_layer			*output_layer;
	int				count;
	int				capacity;
}					t_layer_stack;


typedef struct s_game_data
{
	t_map		*map;
	t_dvector2	player;
	int			player_dir;
	t_ray		ray[1920];
	int			fov;
	int			width;
	int			height;
	double		center;
}				t_game_data;

typedef struct s_game
{
	void			*mlx;
	void			*win;
	int				width;
	int				height;
	void			*hook_callback;
	char			*title;
	int				is_running;
	t_game_data		*data;
	double			delta_time;
	double			last_frame;
	t_layer_stack	*layers;
	t_layer_stack   *textures;
	void			*update_callback;
	int				count;
}					t_game;

#endif