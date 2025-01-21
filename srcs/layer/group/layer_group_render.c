/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   layer_group_render.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmorot <mmorot@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 00:18:18 by mmorot            #+#    #+#             */
/*   Updated: 2025/01/22 00:18:18 by mmorot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "layer.h"

static inline unsigned int	ft_max(unsigned int x, unsigned int y)
{
	if (x > y)
	{
		return (x);
	}
	return (y);
}

static inline unsigned int	ft_min(unsigned int x, unsigned int y)
{
	if (x < y)
	{
		return (x);
	}
	return (y);
}

void	layer_group_render(t_layer *group, t_layer *output)
{
	unsigned int	x;
	unsigned int	stride;
	t_layer_group	process;

	if (!group || !output || group->type != GROUP_LAYER)
		return ;
	process.start_x = ft_max(0, group->offset_x);
	process.end_x = ft_min(output->width, group->offset_x + group->width);
	process.start_y = ft_max(0, group->offset_y);
	process.end_y = ft_min(output->height, group->offset_y + group->height);
	while (process.start_y < process.end_y)
	{
		x = process.start_x;
		stride = process.start_y * output->width;
		while (x < process.end_x)
		{
			get_depth_layer_color(group->layers, x - group->offset_x,
				process.start_y - group->offset_y, &output->data[stride + x]);
			x++;
		}
		process.start_y++;
	}
}
