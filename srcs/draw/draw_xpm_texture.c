#include "draw.h"
#include "layer.h"
#include <../minilibx-linux/mlx.h>
#include <math.h>
#include <stdio.h>

static void	copy_texture_line(t_layer *layer, unsigned int *data,
		t_vector2 position, t_texture_info info)
{
	int				x;
	int				src_x;
	unsigned int	color;

	x = info.start_x;
	while (x < info.end_x)
	{
		src_x = x - (int)position.x; 
		color = data[info.src_offset + src_x];
		layer_set_pixel(layer, x, info.y, int_to_pixel(color));
		x++;
	}
}

static int	get_image(t_texture_info *info, void *mlx, char *path)
{
	info->img = mlx_xpm_file_to_image(mlx, path, &info->width, &info->height);
	if (!info->img && (printf("Error: Could not load XPM file: %s\n", path)
			|| 1))
		return (0);
	info->data = (unsigned int *)mlx_get_data_addr(info->img,
			&info->mlx_data.bpp, &info->mlx_data.line_len,
			&info->mlx_data.endian);
	if (!info->data && (mlx_destroy_image(mlx, info->img) || 1))
		return (0);
	return (1);
}

void	draw_xpm_texture(void *mlx, t_layer *layer, t_vector2 position,
		char *xpm_path)
{
	void			*img;
	unsigned int	*data;
	t_texture_info	info;
	t_mlx_data		mlx_data;

	if (!layer || !xpm_path || !mlx)
		return ;
	if (!get_image(&info, mlx, xpm_path))
		return ;
	info.start_x = fmax(0, (int)position.x);
	info.start_y = fmax(0, (int)position.y);
	info.end_x = fmin(layer->width, (int)position.x + info.width);
	info.end_y = fmin(layer->height, (int)position.y + info.height);
	info.y = info.start_y;
	while (info.y < info.end_y)
	{
		info.src_offset = (info.y - (int)position.y) * info.width;
		copy_texture_line(layer, data, position, info);
		info.y++;
	}
	mlx_destroy_image(mlx, img);
}
