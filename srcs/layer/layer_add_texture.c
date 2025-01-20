#include <stdio.h>
#include "draw.h"
#include "layer.h"
#include <../minilibx-linux/mlx.h>
#include <math.h>

static inline void	copy_texture_line(t_layer *layer,
	unsigned int *data, t_texture_info info)
{
	unsigned int	x;
	unsigned int	y;
	unsigned int	pos;
	unsigned int	end;

	x = info.start_x;
	end = info.end_x;
	y = info.y * layer->width;
	while (x < end)
	{
		pos = y + x;
		layer->data[pos] = data[pos];
		x++;
	}
}

static inline int	get_image(t_texture_info *info, void *mlx, char *path)
{
	info->img = mlx_xpm_file_to_image(mlx, path, &info->end_x, &info->end_y);
	if (!info->img)
	{
		printf("Error: Could not load XPM file: %s\n", path);
		return (0);
	}
	info->data = (unsigned int *)mlx_get_data_addr(info->img,
			&info->mlx_data.bpp, &info->mlx_data.line_len,
			&info->mlx_data.endian);
	if (!info->data)
	{
		mlx_destroy_image(mlx, info->img);
		return (0);
	}
	return (1);
}

static void	init_default_texture_info(t_texture_info *info)
{
	info->start_x = 0;
	info->start_y = 0;
	info->end_x = 0;
	info->end_y = 0;
	info->y = 0;
	info->img = NULL;
	info->data = NULL;
	info->src_offset = 0;
}

t_layer	*layer_add_texture(void *mlx, t_layer_stack *stack, char *path,
		int z_index)
{
	t_texture_info	info;
	t_layer			*new_layer;

	if (!mlx || !stack || !path)
		return (NULL);
	init_default_texture_info(&info);
	if (!get_image(&info, mlx, path))
		return (NULL);
	new_layer = layer_create(mlx, info.end_x, info.end_y, z_index);
	if (!new_layer)
	{
		mlx_destroy_image(mlx, info.img);
		return (NULL);
	}
	while (info.y < info.end_y)
	{
		copy_texture_line(new_layer, info.data, info);
		info.y++;
	}
	layer_stack_add(stack, new_layer);
	mlx_destroy_image(mlx, info.img);
	return (new_layer);
}
