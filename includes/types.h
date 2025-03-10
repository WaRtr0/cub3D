/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   types.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmorot <mmorot@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 00:20:16 by mmorot            #+#    #+#             */
/*   Updated: 2025/01/22 00:28:51 by mmorot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TYPES_H
# define TYPES_H

# define LAYER_STACK_CAPACITY 80

# include <stdbool.h>
// # include "raycast.h"
# include "types.h"
# include "cub.h"

typedef enum e_dir
{
	NORTH,
	EAST,
	SOUTH,
	WEST
}	t_dir;

typedef enum e_map_tile
{
	E = 0, // empty
	H = 1, // hidden door
	P = 2, // player
	W = 3, // wall
	D = 4, // door
	C = 5 // closing door
}	t_map_tile;

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

// # define M_PI 3.14159265358979323846
typedef struct s_raycast_data
{
	t_vector2	ray_pos;
	t_vector2	ray_dir;
	t_vector2	delta_dist;
	t_vector2	side_dist;
	t_vector2	step;
	t_vector2	map_check;
	double		wall_dist;
	double		wall_x;
	int			side;
	bool		hit;
}				t_raycast_data;

typedef enum e_face
{
	N_FACE = 0,
	E_FACE = 1,
	S_FACE = 2,
	W_FACE = 3,
	D_FACE = 4,
}				t_face;

typedef struct s_ray
{
	double		distance;
	double		percent;
	int			face;
	double		offset_angle_rad;								
}				t_ray;

typedef struct s_map
{
	t_map_tile	*tiles;
	int			width;
	int			height;
}	t_map;

typedef struct s_pixel
{
	unsigned int	r;
	unsigned int	g;
	unsigned int	b;
	unsigned int	a;
}					t_pixel;

typedef enum e_layer_type
{
	GROUP_LAYER = 0,
	LAYER = 1,
}	t_layer_type;

typedef struct s_layer
{
	t_layer_type			type;
	void					*img;
	unsigned int			*data;
	struct s_layer_stack	*layers;
	unsigned int			width;
	unsigned int			height;
	int						offset_x;
	int						offset_y;
	int						z_index;
	int						bits_per_pixel;
	int						line_length;
	int						endian;
	bool					visible;
	bool					is_volatile;
	bool					*volatile_update;
	unsigned int			*volatile_data;
	bool					mask;
	t_pixel					clear_color;
}	t_layer;

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

typedef struct s_door
{
	int			pos;
	long long	timestamp;
	int			start;
}				t_door;

typedef struct s_game_data
{
	t_map		*map;
	t_vector2	player;
	double		yaw;
	double		pitch;
	t_ray		ray[(OUTPUT_WIDTH / RATIO)];
	bool		is_warping;
	int			fov;
	int			width;
	int			height;
	double		center;
}				t_game_data;

typedef struct s_player_state
{
	bool	running;
	int		move_dir[4];
	int		key_yaw;
}				t_player_state;

typedef struct s_game
{
	void			*mlx;
	void			*win;
	int				width;
	int				height;
	void			*hook_callback;
	void			*hook_release;
	void			*hook_mouse_move;
	void			*hook_mouse_press;
	char			*title;
	int				is_running;
	t_game_data		*data;
	unsigned int	scale_3d;
	double			delta_time;
	double			last_frame;
	t_layer_stack	*layers;
	t_layer_stack	*textures;
	void			*update_callback;
	int				count;
	t_player_state	player_state;
}					t_game;

#endif