/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_checks_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: garivo <garivo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/23 00:11:50 by garivo            #+#    #+#             */
/*   Updated: 2025/01/17 18:47:57 by garivo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	check_map_char(t_parsing *map)
{
	size_t	i;
	size_t	j;
	char	*cmap;

	i = 0;
	while (i < (unsigned int)map->height)
	{
		j = 0;
		cmap = get_line(map, i);
		while (cmap[j])
		{
			if (!(cmap[j] == '0' || cmap[j] == '1' || cmap[j] == ' '
					|| cmap[j] == 'D'))
				if (!check_dir(map, cmap, i, j))
					return (0);
			j++;
		}
		i++;
	}
	return (1);
}

int	check_border(t_parsing *map, char *cmap, size_t i, size_t j)
{
	if (i == 0 || i == (unsigned int)map->height - 1
		|| j == 0 || j == (unsigned int)map->width - 1)
		if (cmap[j] != ' ' && cmap[j] != '1')
			return (0);
	return (1);
}

int	check_closure(t_parsing	*map, char *cmap, size_t i, size_t j)
{
	if ((cmap[j] == '0' || cmap[j] == 'N' || cmap[j] == 'S'
			|| cmap[j] == 'E' || cmap[j] == 'W' || cmap[j] == 'D')
		&& !(i == 0 || i == (unsigned int)map->height
			|| j == 0 || j == (unsigned int)map->width - 1))
	{
		if (cmap[j - 1] == ' ' || cmap[j + 1] == ' '
			|| get_line(map, i - 1)[j] == ' ' || get_line(map, i + 1)[j] == ' ')
			return (0);
	}
	if (cmap[j] == 'D' && (!(cmap[j - 1] == '1' && cmap[j + 1] == '1')
			&& !(get_line(map, i - 1)[j] == '1'
			&& get_line(map, i + 1)[j] == '1')))
		return (prerr("Error\nInvalid door position\n"), 0);	
	return (1);
}

int	check_map_validity(t_parsing *map)
{
	size_t	i;
	size_t	j;
	char	*cmap;

	i = 0;
	while (i < (unsigned int)map->height)
	{
		j = 0;
		cmap = get_line(map, i);
		while (cmap[j])
		{
			if (!check_border(map, cmap, i, j))
				return (0);
			if (!check_closure(map, cmap, i, j))
				return (0);
			j++;
		}
		i++;
	}
	return (1);
}

int	check_map(t_parsing *map)
{
	if (!map->map)
		return (0);
	if (map->height < 3 || map->width < 3)
		return (prerr("Error\nMap is too small or empty\n"), 0);
	if (!check_map_char(map))
		return (0);
	if (!check_map_validity(map))
		return (prerr("Error\nMap invalid\n"), 0);
	return (1);
}
