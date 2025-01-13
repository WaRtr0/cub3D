/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_map_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: garivo <garivo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 19:50:57 by garivo            #+#    #+#             */
/*   Updated: 2025/01/13 19:51:13 by garivo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

size_t	get_max_line(char **lines)
{
	size_t	i;
	size_t	max;

	i = 0;
	max = 0;
	while (lines[i])
	{
		if (ft_strlen(lines[i]) > max)
			max = ft_strlen(lines[i]);
		i++;
	}
	return (max);
}
