#ifndef DRAW_H
# define DRAW_H

# include "font.h"
# include "types.h"

typedef struct s_draw_triangle_fill
{
	t_vector2	min;
	t_vector2	max;
	t_vector2	p;
	float		area;
	float		area1;
	float		area2;
	float		area3;
}				t_draw_triangle_fill;


typedef struct s_triangle_vector
{
	t_vector2	a;
	t_vector2	b;
	t_vector2	c;
}				t_triangle_vector;

typedef struct s_mlx_data
{
	int			bpp;
	int			line_len;
	int			endian;
}		t_mlx_data;		
typedef struct s_texture_info
{
	int				start_x;
	int				start_y;
	int				end_x;
	int				end_y;
	int				y;
	void			*img;
	unsigned int	*data;
	int				width;
	int				height;
	t_mlx_data		mlx_data;
	int				src_offset;
}				t_texture_info;



void			draw_line(t_layer *layer, t_vector2 start, t_vector2 end,
					t_pixel color);

void			draw_circle(t_layer *layer, t_vector2 center, int radius,
					t_pixel color);
void			draw_circle_fill(t_layer *layer, t_vector2 center, int radius,
					t_pixel color);

void			draw_text(t_layer *layer, t_vector2 position, t_font *font,
					const char *text);

void			draw_rect_fill(t_layer *layer, t_vector2 start, t_vector2 end,
					t_pixel color);

void			draw_rect(t_layer *layer, t_vector2 start, t_vector2 end,
					t_pixel color);

void			draw_triangle(t_layer *layer, t_triangle_vector vector,
					t_pixel color);

void			draw_triangle_fill(t_layer *layer, t_triangle_vector vector,
					t_pixel color);

void			draw_xpm_texture(void *mlx, t_layer *layer, t_vector2 position,
					char *xpm_path);

#endif