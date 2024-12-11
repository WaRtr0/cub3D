#include "draw.h"
#include "layer.h"
#include <../minilibx-linux/mlx.h>
#include <math.h>
#include <stdio.h>

static void    copy_texture_line(t_layer *layer, unsigned int *data,
        t_vector2 position, t_texture_info info)
{
    int                x;
    int                src_x;
    unsigned int    color;
    t_pixel            pixel;

    x = info.start_x;
    while (x < info.end_x)
    {
        src_x = x - (int)position.x; 
        color = data[info.src_offset + src_x];
        pixel = int_to_pixel(color);
        pixel.a = 255 - pixel.a;
        layer_set_pixel(layer, x, info.y, pixel);
        x++;
    }
}

void    draw_xpm_texture(void *mlx, t_layer *layer, t_vector2 position,
        char *xpm_path)
{
    void            *img;
    unsigned int    *data;
    t_texture_info    info;
    int                img_size[2];
    t_mlx_data        mlx_data;

    if (!layer || !xpm_path || !mlx)
        return ;
    img = mlx_xpm_file_to_image(mlx, xpm_path, &img_size[0], &img_size[1]);
    if (!img && (printf("Error: Could not load XPM file: %s\n", xpm_path) || 1))
        return ;
    data = (unsigned int *)mlx_get_data_addr(img, &mlx_data.bpp,
            &mlx_data.line_len, &mlx_data.endian);
    if (!data && (mlx_destroy_image(mlx, img) || 1))
        return ;
    info.start_x = fmax(0, (int)position.x);
    info.start_y = fmax(0, (int)position.y);
    info.end_x = fmin(layer->width, (int)position.x + img_size[0]);
    info.end_y = fmin(layer->height, (int)position.y + img_size[1]);
    info.y = info.start_y;
    while (info.y < info.end_y)
    {
        info.src_offset = (info.y - (int)position.y) * img_size[0];
        copy_texture_line(layer, data, position, info);
        info.y++;
    }
    mlx_destroy_image(mlx, img);
}