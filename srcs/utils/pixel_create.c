/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pixel_create.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmorot <mmorot@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 00:16:21 by mmorot            #+#    #+#             */
/*   Updated: 2025/01/22 00:16:21 by mmorot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "types.h"

t_pixel	pixel_create(int r, int g, int b, int a)
{
	t_pixel	pixel;

	pixel.r = r;
	pixel.g = g;
	pixel.b = b;
	pixel.a = a;
	return (pixel);
}
