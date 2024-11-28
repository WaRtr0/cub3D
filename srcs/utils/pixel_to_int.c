#include "types.h"

int	pixel_to_int(t_pixel pixel)
{
	return (pixel.a << 24 | pixel.r << 16 | pixel.g << 8 | pixel.b);
}
