#ifndef DRAW_H
# define DRAW_H

# include "types.h"
# include "font.h"


void	draw_line(t_layer *layer, t_vector2 start, t_vector2 end,
			t_pixel color);

void	draw_circle(t_layer *layer, t_vector2 center, int radius,
			t_pixel color);
void	draw_circle_fill(t_layer *layer, t_vector2 center, int radius,
			t_pixel color);

void	draw_text(t_layer *layer, t_vector2 position, t_font *font,
			const char *text);

void	draw_rect(t_layer *layer, t_vector2 start, t_vector2 end,
			t_pixel color);

void draw_triangle(t_layer *layer, t_vector2 a, t_vector2 b, t_vector2 c, t_pixel color);
void draw_triangle_fill(t_layer *layer, t_vector2 a, t_vector2 b, t_vector2 c, t_pixel color);

void    draw_xpm_texture(void *mlx, t_layer *layer, t_vector2 position, 
    char *xpm_path);

#endif