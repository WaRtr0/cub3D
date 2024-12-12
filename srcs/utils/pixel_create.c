#include "types.h"

t_pixel	pixel_create(int r, int g, int b, int a)
{
	t_pixel pixel;

	pixel.r = r;
	pixel.g = g;
	pixel.b = b;
	pixel.a = a;
	return (pixel);
}