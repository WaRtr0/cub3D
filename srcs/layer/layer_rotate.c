#include "layer.h"
#include <math.h>
#include <stdlib.h>

void    layer_rotate(t_layer *layer, int deg)
{
    // int i;
    // int j;
    // int x;
    // int y;
    // int new_x;
    // int new_y;
    // int width;
    // int height;
    // unsigned int *data;
    // void *mlx;
    // int		bits_per_pixel;
	// int		line_length;
	// int		endian;
    // unsigned int *new_data;
    // if (!layer)
    //     return ;
    // width = layer->width;
    // height = layer->height;
    // data = layer->data;
    // mlx = mlx_new_image(mlx, width, height);
    // new_data = (unsigned int *)mlx_get_data_addr(layer->img, &bits_per_pixel,
	// 		&line_length, &endian);
    // if (!layer->img)
	// {
	// 	free(layer);
	// 	return ;
	// }
    // i = 0;
    // while (i < height)
    // {
    //     j = 0;
    //     while (j < width)
    //     {
    //         x = j - width / 2;
    //         y = i - height / 2;
    //         new_x = x * cos(deg * M_PI / 180) - y * sin(deg * M_PI / 180);
    //         new_y = x * sin(deg * M_PI / 180) + y * cos(deg * M_PI / 180);
    //         new_x += width / 2;
    //         new_y += height / 2;
    //         if (new_x >= 0 && new_x < width && new_y >= 0 && new_y < height)
    //             new_data[i * width + j] = data[new_y * width + new_x];
    //         j++;
    //     }
    //     i++;
    // }
    // // free(layer->data);
    // if (layer->img)
	// 	mlx_destroy_image(layer->mlx, layer->img);
    // layer->data = new_data;
}