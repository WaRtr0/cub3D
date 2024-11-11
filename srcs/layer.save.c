#include "layer.h"
#include <math.h>
#include "../libft/libft.h"

t_layer *layer_create(void *mlx, int width, int height, int z_index)
{
    t_layer *layer;

    layer = (t_layer *)malloc(sizeof(t_layer));
    if (!layer)
        return (NULL);

    layer->width = width;
    layer->height = height;
    layer->z_index = z_index;
    layer->scale = 1;
    layer->offset_x = 0;
    layer->offset_y = 0;
    layer->visible = 1;
    layer->img = mlx_new_image(mlx, width, height);
    if (!layer->img)
    {
        free(layer);
        return (NULL);
    }

    layer->addr = mlx_get_data_addr(layer->img, &layer->bits_per_pixel,
        &layer->line_length, &layer->endian);
    layer->clear_color = pixel_create(0, 0, 0, 0);

    return (layer);
}

void layer_destroy(void *mlx, t_layer *layer)
{
    if (!layer)
        return;
    if (layer->img)
        mlx_destroy_image(mlx, layer->img);
    free(layer);
}

void layer_set_pixel(t_layer *layer, int x, int y, t_pixel color)
{
    char    *dst;
    int     offset;

    if (x < 0 || x >= layer->width || y < 0 || y >= layer->height)
        return;

    offset = (y * layer->line_length) + (x * (layer->bits_per_pixel / 8));
    dst = layer->addr + offset;
    *(unsigned int*)dst = pixel_to_int(color);
}


void layer_set_offset(t_layer *layer, int x, int y)
{
    layer->offset_x = x;
    layer->offset_y = y;
}

void layer_get_offset(t_layer *layer, int *x, int *y)
{
    *x = layer->offset_x;
    *y = layer->offset_y;
}

void layer_set_scale(t_layer *layer, int scale)
{
    layer->scale = scale;
}



t_pixel layer_get_pixel(t_layer *layer, int x, int y)
{
    char    *src;
    int     offset;

    if (x - layer->offset_x < 0 || x - layer->offset_x >= layer->width || y - layer->offset_y < 0 || y - layer->offset_y >= layer->height)
        return pixel_create(0, 0, 0, 0);

    offset = ((y - layer->offset_y) * layer->line_length) + ((x - layer->offset_x) * (layer->bits_per_pixel / 8));
    src = layer->addr + offset;
    return int_to_pixel(*(unsigned int*)src);
}

void layer_clear(t_layer *layer)
{
    layer_fill(layer, layer->clear_color);
}

void layer_fill(t_layer *layer, t_pixel color)
{
    int x;
    int y;

    for (y = 0; y < layer->height; y++)
    {
        for (x = 0; x < layer->width; x++)
        {
            layer_set_pixel(layer, x, y, color);
        }
    }
}

// Layer stack implementation
t_layer_stack *layer_stack_create(int initial_capacity)
{
    t_layer_stack *stack;

    stack = (t_layer_stack *)malloc(sizeof(t_layer_stack));
    if (!stack)
        return (NULL);

    stack->layers = (t_layer **)malloc(sizeof(t_layer *) * initial_capacity);
    if (!stack->layers)
    {
        free(stack);
        return (NULL);
    }

    stack->count = 0;
    stack->capacity = initial_capacity;
    return (stack);
}

void layer_stack_destroy(void *mlx, t_layer_stack *stack)
{
    int i;

    if (!stack)
        return;

    for (i = 0; i < stack->count; i++)
        layer_destroy(mlx, stack->layers[i]);
    
    free(stack->layers);
    free(stack);
}

int layer_stack_add(t_layer_stack *stack, t_layer *layer)
{
    t_layer **new_layers;
    int     new_capacity;

    if (stack->count >= stack->capacity)
    {
        new_capacity = stack->capacity * 2;
        new_layers = (t_layer **)realloc(stack->layers, 
            sizeof(t_layer *) * new_capacity);
        if (!new_layers)
            return (0);
        stack->layers = new_layers;
        stack->capacity = new_capacity;
    }

    stack->layers[stack->count++] = layer;
    layer_stack_sort(stack);
    return (1);
}

// Tri des calques par z_index
void layer_stack_sort(t_layer_stack *stack)
{
    int i;
    int j;
    t_layer *temp;

    for (i = 0; i < stack->count - 1; i++)
    {
        for (j = 0; j < stack->count - i - 1; j++)
        {
            if (stack->layers[j]->z_index > stack->layers[j + 1]->z_index)
            {
                temp = stack->layers[j];
                stack->layers[j] = stack->layers[j + 1];
                stack->layers[j + 1] = temp;
            }
        }
    }
}

t_layer *layer_stack_get(t_layer_stack *stack, int z_index)
{
    int i;

    for (i = 0; i < stack->count; i++)
    {
        if (stack->layers[i]->z_index == z_index)
            return (stack->layers[i]);
    }
    return (NULL);
}

#include <stdio.h>

void    layer_stack_render(t_layer_stack *stack, void *mlx, void *win)
{
    static t_layer  *output_layer = NULL;
    int             i;
    int             x;
    int             y;
    unsigned int    *output_data;
    unsigned int    *layer_data;
    int             offset;

    if (stack->count == 0)
        return ;

    // Création unique du calque de sortie
    if (!output_layer)
    {
        output_layer = layer_create(mlx, stack->layers[0]->width, 
            stack->layers[0]->height, 0);
        if (!output_layer)
            return ;
    }

    output_data = (unsigned int *)output_layer->addr;

    // Optimisation : copier directement le premier calque non transparent
    i = 0;
    while (i < stack->count)
    {
        layer_data = (unsigned int *)stack->layers[i]->addr;
        if (stack->layers[i]->offset_x == 0 && 
            stack->layers[i]->offset_y == 0 && 
            stack->layers[i]->width == output_layer->width && 
            stack->layers[i]->height == output_layer->height)
        {
            ft_memcpy(output_data, layer_data, 
                output_layer->width * output_layer->height * sizeof(unsigned int));
            break ;
        }
        i++;
    }

    // Composer les calques restants
    i++;
    while (i < stack->count)
    {
        layer_data = (unsigned int *)stack->layers[i]->addr;
        int start_y = fmax(0, stack->layers[i]->offset_y);
        int end_y = fmin(output_layer->height, 
            stack->layers[i]->offset_y + stack->layers[i]->height);
        int start_x = fmax(0, stack->layers[i]->offset_x);
        int end_x = fmin(output_layer->width, 
            stack->layers[i]->offset_x + stack->layers[i]->width);

        for (y = start_y; y < end_y; y++)
        {
            for (x = start_x; x < end_x; x++)
            {
                int layer_x = x - stack->layers[i]->offset_x;
                int layer_y = y - stack->layers[i]->offset_y;
                unsigned int current = layer_data[layer_y * 
                    stack->layers[i]->width + layer_x];
                unsigned char alpha = (current >> 24) & 0xFF;

                if (alpha == 255)
                {
                    output_data[y * output_layer->width + x] = current;
                }
                else if (alpha > 0)
                {
                    unsigned int dest = output_data[y * output_layer->width + x];
                    float a = alpha / 255.0f;
                    unsigned char r = ((current >> 16) & 0xFF) * a + 
                        ((dest >> 16) & 0xFF) * (1 - a);
                    unsigned char g = ((current >> 8) & 0xFF) * a + 
                        ((dest >> 8) & 0xFF) * (1 - a);
                    unsigned char b = (current & 0xFF) * a + 
                        (dest & 0xFF) * (1 - a);
                    output_data[y * output_layer->width + x] = 
                        (255 << 24) | (r << 16) | (g << 8) | b;
                }
            }
        }
        i++;
    }
    mlx_put_image_to_window(mlx, win, output_layer->img, 0, 0);
}

// Utility functions
t_pixel pixel_create(int r, int g, int b, int a)
{
    t_pixel pixel;

    pixel.r = r;
    pixel.g = g;
    pixel.b = b;
    pixel.a = a;
    return (pixel);
}

int pixel_to_int(t_pixel pixel)
{
    return (pixel.a << 24 | pixel.r << 16 | pixel.g << 8 | pixel.b);
}

t_pixel int_to_pixel(int color)
{
    return pixel_create(
        (color >> 16) & 0xFF,
        (color >> 8) & 0xFF,
        color & 0xFF,
        (color >> 24) & 0xFF
    );
}