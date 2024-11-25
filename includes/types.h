#ifndef TYPES_H
# define TYPES_H

typedef struct s_vector2
{
	double			x;
	double			y;
}					t_vector2;

typedef struct s_dvector2
{
	unsigned int	x;
	unsigned int	y;
}					t_dvector2;	

typedef struct s_pixel
{
	unsigned int	r;
	unsigned int	g;
	unsigned int	b;
	unsigned int	a;
}					t_pixel;

typedef struct s_img
{
	void	*img;
	char	*addr;
	int		bpp;
	int		line_len;
	int		endian;
	int		w;
	int		h;
}					t_img;

typedef struct s_layer
{
	void			*img;
	char			*addr;
	void			*mlx;
	int				bits_per_pixel;
	int				line_length;
	int				endian;
	int				width;
	int				height;
	int				scale;
	int				offset_x;
	int				offset_y;
	int				visible;
	int				z_index;
	t_pixel			clear_color;
}					t_layer;

typedef struct s_layer_stack
{
	t_layer			**layers;
	t_layer			*output_layer;
	int				count;
	int				capacity;
}					t_layer_stack;

typedef struct s_game
{
	void			*mlx;
	void			*win;
	int				width;
	int				height;
	void			*hook_callback;
	char			*title;
	int				is_running;
	double			delta_time;
	double			last_frame;
	t_layer_stack	*layers;
	void			*update_callback;
	int				count;
}					t_game;

#endif