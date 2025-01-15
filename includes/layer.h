#ifndef LAYER_H
# define LAYER_H

# include "types.h"
# include <../minilibx-linux/mlx.h>
# include <stdlib.h>

typedef struct s_layer_group
{
	unsigned int	start_x;
	unsigned int	start_y;
	unsigned int	end_x;
	unsigned int	end_y;
}	t_layer_group;

typedef struct s_handle_depth
{
	t_layer			*layer;
	unsigned int	pos;
	int				i;
	t_dvector2		src;
}	t_handle_depth;

t_layer			*layer_create(void *mlx, int width, int height, int z_index);
void			layer_destroy(void *mlx, t_layer *layer);
void			layer_clear(t_layer *layer);
void			layer_set_pixel(t_layer *layer, int x, int y, t_pixel color);
t_pixel			layer_get_pixel(t_layer *layer, int x, int y);
void			layer_fill(t_layer *layer, t_pixel color);
void			layer_set_clear_color(t_layer *layer, t_pixel color);
void			layer_set_offset(t_layer *layer, int x, int y);
void			layer_get_offset(t_layer *layer, int *x, int *y);
void			layer_set_scale(t_layer *layer, int scale);
void			layer_set_visible(t_layer *layer, int visible);

// Layer duplication
int				layer_data_dupe(t_layer *src, unsigned int *dst);
int				layer_dupe(t_layer *src, t_layer *dst);

void			layer_split_fill(t_layer *layer, t_pixel color1,
					t_pixel color2);

// texturing

t_layer			*layer_add_texture(void *mlx, t_layer_stack *stack, char *path,
					int z_index);

// group layer

t_layer			*layer_group_create(int width, int height, int z_index);
int				layer_group_add(t_layer *group, t_layer *layer);
t_layer			*layer_group_get(t_layer *group, int z_index);
void			layer_group_destroy(void *mlx, t_layer *group);

void			get_depth_layer_color(t_layer_stack *stack, unsigned int x,
					unsigned int y, unsigned int *color);
void			layer_group_render(t_layer *group, t_layer *output);
// Layer volatile

void			layer_volatile_on(t_layer *layer);
void			layer_volatile_off(t_layer *layer);

// Layer rotation
void			layer_rotate(t_layer *layer, int deg);
// Layer stack methods
t_layer_stack	*layer_stack_create(void);
void			layer_stack_destroy(void *mlx, t_layer_stack *stack);
int				layer_stack_add(t_layer_stack *stack, t_layer *layer);
void			layer_stack_remove(void *mlx, t_layer_stack *stack,
					int z_index);
void			layer_stack_render(t_layer_stack *stack, void *mlx, void *win);
t_layer			*layer_stack_get(t_layer_stack *stack, int z_index);

void			layer_stack_render(t_layer_stack *stack, void *mlx, void *win);

// Utility functions
t_pixel			pixel_create(int r, int g, int b, int a);
unsigned int	pixel_to_int(t_pixel pixel);
t_pixel			int_to_pixel(unsigned int color);

#endif