#include "layer.h"
#include "../libft/libft.h"

int	layer_dupe(t_layer *src, t_layer *dst)
{
	if (!src || !dst)
		return (0);
	if (src->width != dst->width || src->height != dst->height)
		return (0);
	ft_memcpy(dst->data, src->data, src->width * src->height * 4);
	return (1);
}