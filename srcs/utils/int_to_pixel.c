#include "types.h"
#include "layer.h"

t_pixel	int_to_pixel(int color)
{
	return (pixel_create((color >> 16) & 0xFF, (color >> 8) & 0xFF,
			color & 0xFF, (color >> 24) & 0xFF));
}