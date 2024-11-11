#include "layer.h"
#include "font.h"
#include <math.h>

void draw_line(t_layer *layer, t_vector2 start, t_vector2 end, t_pixel color)
{
    t_vector2 delta;
    t_vector2 step;
    t_vector2 current;
    int longest;
    int i;

    delta.x = end.x - start.x;
    delta.y = end.y - start.y;
    longest = abs((int)delta.x) > abs((int)delta.y) ? abs((int)delta.x) : abs((int)delta.y);
    step.x = delta.x / (double)longest;
    step.y = delta.y / (double)longest;
    current = start;
    i = 0;
    while (i < longest)
    {
        layer_set_pixel(layer, (int)current.x, (int)current.y, color);
        current.x += step.x;
        current.y += step.y;
        i++;
    }
}

void draw_circle(t_layer *layer, t_vector2 center, int radius, t_pixel color)
{
    int x;
    int y;
    int p;

    x = 0;
    y = radius;
    p = 3 - 2 * radius;
    while (x <= y)
    {
        layer_set_pixel(layer, center.x + x, center.y + y, color);
        layer_set_pixel(layer, center.x - x, center.y + y, color);
        layer_set_pixel(layer, center.x + x, center.y - y, color);
        layer_set_pixel(layer, center.x - x, center.y - y, color);
        layer_set_pixel(layer, center.x + y, center.y + x, color);
        layer_set_pixel(layer, center.x - y, center.y + x, color);
        layer_set_pixel(layer, center.x + y, center.y - x, color);
        layer_set_pixel(layer, center.x - y, center.y - x, color);
        if (p < 0)
            p += 4 * x + 6;
        else
        {
            p += 4 * (x - y) + 10;
            y--;
        }
        x++;
    }
}

void draw_circle_fill(t_layer *layer, t_vector2 center, int radius, t_pixel color)
{
    int x;
    int y;
    int p;

    x = 0;
    y = radius;
    p = 3 - 2 * radius;
    while (x <= y)
    {
        draw_line(layer, (t_vector2){center.x - x, center.y + y}, (t_vector2){center.x + x, center.y + y}, color);
        draw_line(layer, (t_vector2){center.x - x, center.y - y}, (t_vector2){center.x + x, center.y - y}, color);
        draw_line(layer, (t_vector2){center.x - y, center.y + x}, (t_vector2){center.x + y, center.y + x}, color);
        draw_line(layer, (t_vector2){center.x - y, center.y - x}, (t_vector2){center.x + y, center.y - x}, color);
        if (p < 0)
            p += 4 * x + 6;
        else
        {
            p += 4 * (x - y) + 10;
            y--;
        }
        x++;
    }
}

void draw_rect(t_layer *layer, t_vector2 start, t_vector2 end, t_pixel color)
{
    int x;
    int y;

    x = start.x;
    while (x <= end.x)
    {
        y = start.y;
        while (y <= end.y)
        {
            layer_set_pixel(layer, x, y, color);
            y++;
        }
        x++;
    }
}

void draw_rect_fill(t_layer *layer, t_vector2 start, t_vector2 end, t_pixel color)
{
    int x;
    int y;

    x = start.x;
    while (x <= end.x)
    {
        y = start.y;
        while (y <= end.y)
        {
            layer_set_pixel(layer, x, y, color);
            y++;
        }
        x++;
    }
}

void draw_triangle(t_layer *layer, t_vector2 a, t_vector2 b, t_vector2 c, t_pixel color)
{
    draw_line(layer, a, b, color);
    draw_line(layer, b, c, color);
    draw_line(layer, c, a, color);
}
#include <stdio.h>

void draw_triangle_fill(t_layer *layer, t_vector2 a, t_vector2 b, t_vector2 c, t_pixel color)
{
    t_vector2 min;
    t_vector2 max;
    t_vector2 p;
    float area;
    float area1;
    float area2;
    float area3;

    // Find the bounding rectangle of the triangle
    min.x = floorf(fminf(fminf(a.x, b.x), c.x));
    min.y = floorf(fminf(fminf(a.y, b.y), c.y));
    max.x = ceilf(fmaxf(fmaxf(a.x, b.x), c.x));
    max.y = ceilf(fmaxf(fmaxf(a.y, b.y), c.y));

    // Pre-compute the area of the triangle
    area = (b.x - a.x)*(c.y - a.y) - (b.y - a.y)*(c.x - a.x);

    // Loop over each pixel in the bounding rectangle
    for (p.x = min.x; p.x <= max.x; p.x++)
    {
        for (p.y = min.y; p.y <= max.y; p.y++)
        {
            // Compute areas of sub-triangles
            area1 = (b.x - p.x)*(c.y - p.y) - (b.y - p.y)*(c.x - p.x);
            area2 = (c.x - p.x)*(a.y - p.y) - (c.y - p.y)*(a.x - p.x);
            area3 = (a.x - p.x)*(b.y - p.y) - (a.y - p.y)*(b.x - p.x);

            // Check if the point is inside the triangle
            if ((area >= 0 && area1 >= 0 && area2 >= 0 && area3 >= 0) ||
                (area <= 0 && area1 <= 0 && area2 <= 0 && area3 <= 0))
            {
                layer_set_pixel(layer, p.x, p.y, color);
            }
        }
    }
}



#include <stdio.h>

void draw_glyph(t_layer *layer, t_vector2 position, t_font *font, t_glyph *glyph)
{
    int x;
    int y;
    int bit;
    int i;
    int j;

    // printf("draw_glyph\n");
    // printf("position.x: %.6f\n", position.x);

    if (!layer || !font || !glyph || !glyph->bitmap || glyph->bbx_height <= 0)
    {
        printf("draw_glyph: invalid arguments\n");
        return;
    }

    y = 0;
    while (y < glyph->bbx_height)
    {
        if (!glyph->bitmap[y])
        {
            y++;
            continue;
        }

        // printf("glyph->bitmap[%d]:", y);
        // for (int k = 0; k < (glyph->bbx_width + 7) / 8; k++)
        // {
        //     printf(" %02x", glyph->bitmap[y][k]);
        // }
        // // printf("\n");

        x = 0;
        while (x < glyph->bbx_width)
        {
            bit = (glyph->bitmap[y][x / 8] >> (7 - (x % 8))) & 1;
            if (bit)
            {
                i = 0;
                while (i < font->size)
                {
                    j = 0;
                    while (j < font->size)
                    {
                        if ((position.x + (x + glyph->bbx_x_offset) * font->size + i) >= 0
                            && (position.y + (y + glyph->bbx_y_offset) * font->size + j) >= 0)
                        {
                            layer_set_pixel(layer,
                                            position.x + (x + glyph->bbx_x_offset) * font->size + i,
                                            position.y + (y + glyph->bbx_y_offset) * font->size + j,
                                            font->color);
                        }
                        j++;
                    }
                    i++;
                }
            }
            x++;
        }
        y++;
    }
}

void draw_text(t_layer *layer, t_vector2 position, t_font *font, const char *text)
{
    int i;
    int j;
    t_glyph *glyph;
    t_vector2 current_position;
    double max_height;

    current_position = position;
    i = 0;
    max_height = 0;


    printf("draw_text\n");
    printf("position.x: %.6f | positon.y : %.6f\n", position.x);
    while (text[i] != '\0')
    {
        glyph = NULL;
        j = 0;
        while (j < font->bdf->glyph_count)
        {
            if (font->bdf->glyphs[j].encoding == (int)text[i])
            {
                glyph = &font->bdf->glyphs[j];
                break;
            }
            j++;
        }
        if (glyph && glyph->bitmap)
        {
            printf("glyph->height: %d\n", glyph->bbx_height);
            if (glyph->bbx_height > max_height)
            
                max_height = (double)glyph->bbx_height;
        }
       
        i++;
    }
    i = 0;
    // current_position.y -= max_height * font->size;
    while (text[i] != '\0')
    {
        glyph = NULL;
        j = 0;
        while (j < font->bdf->glyph_count)
        {
            if (font->bdf->glyphs[j].encoding == (int)text[i])
            {
                glyph = &font->bdf->glyphs[j];
                break;
            }
            j++;
        }
        if (glyph && glyph->bitmap)
        {
            draw_glyph(layer, (t_vector2){
                current_position.x,
                current_position.y - (glyph->bbx_y_offset + glyph->bbx_height) * font->size
            
            }, font, glyph);
            // Avancer la position horizontale
            current_position.x += (glyph->d_width + glyph->bbx_x_offset) * font->size;
        }
        else
        {
            // Ajouter un espacement par défaut si le glyphe est introuvable
            current_position.x += font->size;
        }
        i++;
    }
}

void    draw_xpm_texture(void *mlx, t_layer *layer, t_vector2 position, 
    char *xpm_path)
{
    void            *img;
    unsigned int    *data;
    unsigned int    *layer_data;
    int             img_width;
    int             img_height;
    int             bits_per_pixel;
    int             size_line;
    int             endian;
    int             x;
    int             y;

    if (!layer || !xpm_path || !mlx)
        return ;

    img = mlx_xpm_file_to_image(mlx, xpm_path, &img_width, &img_height);
    if (!img)
    {
        printf("Error: Could not load XPM file: %s\n", xpm_path);
        return ;
    }

    data = (unsigned int *)mlx_get_data_addr(img, &bits_per_pixel, 
        &size_line, &endian);
    if (!data)
    {
        mlx_destroy_image(mlx, img);
        return ;
    }

    layer_data = (unsigned int *)layer->addr;

    // Calculer les limites de rendu
    int start_x = fmax(0, (int)position.x);
    int start_y = fmax(0, (int)position.y);
    int end_x = fmin(layer->width, (int)position.x + img_width);
    int end_y = fmin(layer->height, (int)position.y + img_height);

    // Optimisation : copie directe pour les lignes complètes
    for (y = start_y; y < end_y; y++)
    {
        int src_y = y - (int)position.y;
        int dest_offset = y * (layer->line_length / 4) + start_x;
        int src_offset = src_y * (size_line / 4);
        
        for (x = start_x; x < end_x; x++)
        {
            int src_x = x - (int)position.x;
            unsigned int color = data[src_offset + src_x];
            
            if (color != 0)  // Skip transparent pixels
                layer_data[dest_offset + (x - start_x)] = color;
        }
    }
    mlx_destroy_image(mlx, img);
}