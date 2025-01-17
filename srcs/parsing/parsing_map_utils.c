/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_map_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: garivo <garivo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 19:50:57 by garivo            #+#    #+#             */
/*   Updated: 2025/01/17 16:45:19 by garivo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

size_t	get_max_line(char **lines)
{
	size_t	i;
	size_t	j;
	size_t	max;

	i = 0;
	max = 0;
	while (lines[i])
	{
		if (ft_strlen(lines[i]) > max)
		{
			j = 0;
			while (lines[i][j])
			{
				if (j > MAX_WIDTH)
					return (prerr("Error\nMap is too big\n"), 0);
				j++;
			}
			max = j;
		}
		i++;
	}
	return (max);
}
