#include "layer.h"
#include "types.h"

t_pixel	int_to_pixel(unsigned int color)
{
	t_pixel	pixel;

	pixel.a = (color >> 24) & 0xFF;
	pixel.r = (color >> 16) & 0xFF;
	pixel.g = (color >> 8) & 0xFF;
	pixel.b = color & 0xFF;
	return (pixel);
}
