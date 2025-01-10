/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gladius <gladius@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 19:32:42 by garivo            #+#    #+#             */
/*   Updated: 2025/01/09 21:25:23 by gladius          ###   ########.fr       */
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

size_t	get_lines(char **lines)
{
	size_t	i;

	i = 0;
	while (lines[i] && lines[i][0] != '\0')
		i++;
	return (i);
}

char	*get_line(t_parsing *map, size_t i)
{
	if (i >= (unsigned int)map->height)
		return (NULL);
	return (map->map + i * (map->width + 1));
}

int	check_map_last(t_parsing *map, char **lines, size_t i)
{
	unsigned int	last;

	last = i;
	while (lines[i] && lines[i][0] == '\0')
		i++;
	if (i != last && lines[i])
		return (prerr("Error\nMap must be the last element\n"),
			free(map->map), 0);
	return (1);
}

int	extract_map(t_parsing *map, char **lines)
{
	size_t	i;
	size_t	j;

	i = 0;
	map->map = malloc(sizeof(char) * get_lines(lines)
			* (get_max_line(lines) + 1));
	if (!map->map)
		return (0);
	while (lines[i] && i < (unsigned int)map->height)
	{
		j = 0;
		while (lines[i][j])
		{
			map->map[i * (map->width + 1) + j] = lines[i][j];
			j++;
		}
		while (j < (unsigned int)map->width)
			map->map[i * (map->width + 1) + j++] = ' ';
		map->map[i * (map->width + 1) + j] = '\0';
		i++;
	}
	if (!check_map_last(map, lines, i))
		return (0);
	return (1);
}

int	parse_map(t_parsing *map, char **lines)
{
	int	i;

	map->height = get_lines(lines);
	map->width = get_max_line(lines);
	if (!extract_map(map, lines))
		return (0);
	if (!check_map(map))
		return (0);
	i = 0;
	while (i < map->height)
	{
		printf("%s\n", get_line(map, i));
		i++;
	}
	return (1);
}
