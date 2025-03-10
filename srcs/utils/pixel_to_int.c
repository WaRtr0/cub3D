/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pixel_to_int.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmorot <mmorot@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 00:16:18 by mmorot            #+#    #+#             */
/*   Updated: 2025/01/22 00:16:18 by mmorot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "types.h"

unsigned int	pixel_to_int(t_pixel pixel)
{
	return (pixel.a << 24 | pixel.r << 16 | pixel.g << 8 | pixel.b);
}
