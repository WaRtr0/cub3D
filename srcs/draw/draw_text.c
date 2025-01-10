#include "draw.h"
#include "layer.h"
#include <stdio.h>

// void	draw_glyph(t_layer *layer, t_vector2 position, t_font *font,
// 		t_glyph *glyph)
// {
// 	int	x;
// 	int	y;
// 	int	bit;
// 	int	i;
// 	int	j;

// 	if (!layer || !font || !glyph || !glyph->bitmap || glyph->bbx_height <= 0)
// 	{
// 		printf("draw_glyph: invalid arguments\n");
// 		return ;
// 	}
// 	y = 0;
// 	while (y < glyph->bbx_height)
// 	{
// 		if (!glyph->bitmap[y])
// 		{
// 			y++;
// 			continue ;
// 		}
// 		x = 0;
// 		while (x < glyph->bbx_width)
// 		{
// 			bit = (glyph->bitmap[y][x / 8] >> (7 - (x % 8))) & 1;
// 			if (bit)
// 			{
// 				i = 0;
// 				while (i < font->size)
// 				{
// 					j = 0;
// 					while (j < font->size)
// 					{
// 						if ((position.x + (x + glyph->bbx_x_offset) * font->size
// 								+ i) >= 0 && (position.y + (y
// 									+ glyph->bbx_y_offset) * font->size
// 								+ j) >= 0)
// 						{
// 							layer_set_pixel(layer, position.x + (x
// 									+ glyph->bbx_x_offset) * font->size + i,
// 								position.y + (y + glyph->bbx_y_offset)
// 								* font->size + j, font->color);
// 						}
// 						j++;
// 					}
// 					i++;
// 				}
// 			}
// 			x++;
// 		}
// 		y++;
// 	}
// }

// void	draw_text(t_layer *layer, t_vector2 position, t_font *font,
// 		const char *text)
// {
// 	int			i;
// 	int			j;
// 	t_glyph		*glyph;
// 	t_vector2	current_position;
// 	double		max_height;

// 	current_position = position;
// 	i = 0;
// 	max_height = 0;
// 	while (text[i] != '\0')
// 	{
// 		glyph = NULL;
// 		j = 0;
// 		while (j < font->bdf->glyph_count)
// 		{
// 			if (font->bdf->glyphs[j].encoding == (int)text[i])
// 			{
// 				glyph = &font->bdf->glyphs[j];
// 				break ;
// 			}
// 			j++;
// 		}
// 		if (glyph && glyph->bitmap)
// 		{
// 			if (glyph->bbx_height > max_height)
// 				max_height = (double)glyph->bbx_height;
// 		}
// 		i++;
// 	}
// 	i = 0;
// 	while (text[i] != '\0')
// 	{
// 		glyph = NULL;
// 		j = 0;
// 		while (j < font->bdf->glyph_count)
// 		{
// 			if (font->bdf->glyphs[j].encoding == (int)text[i])
// 			{
// 				glyph = &font->bdf->glyphs[j];
// 				break ;
// 			}
// 			j++;
// 		}
// 		if (glyph && glyph->bitmap)
// 		{
// 			draw_glyph(layer, (t_vector2){current_position.x, current_position.y
// 				- (glyph->bbx_y_offset + glyph->bbx_height) * font->size}, font,
// 				glyph);
// 			current_position.x += (glyph->d_width + glyph->bbx_x_offset)
// 				* font->size;
// 		}
// 		else
// 		{
// 			current_position.x += font->size;
// 		}
// 		i++;
// 	}
// }
