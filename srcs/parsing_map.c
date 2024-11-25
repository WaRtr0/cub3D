/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: garivo <garivo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 19:32:42 by garivo            #+#    #+#             */
/*   Updated: 2024/11/23 00:26:37 by garivo           ###   ########.fr       */
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
	while (lines[i])
		i++;
	return (i);
}

char	*get_line(t_map *map, size_t i)
{
	if (i >= map->height)
		return (NULL);
	return (map->map + i * (map->width + 1));
}

int	extract_map(t_game *game, t_map *map, char **lines)
{
	size_t	i;
	size_t	j;

	i = 0;
	map->map = malloc(sizeof(char) * get_lines(lines)
			* (get_max_line(lines) + 1));
	if (!map->map)
		return (0);
	while (lines[i])
	{
		j = 0;
		while (lines[i][j])
		{
			map->map[i * (map->width + 1) + j] = lines[i][j];
			j++;
		}
		while (j < map->width)
		{
			map->map[i * (map->width + 1) + j] = ' ';
			j++;
		}
		map->map[i * (map->width + 1) + j] = '\0';
		i++;
	}
	return (1);
}

int	parse_map(t_game *game, t_map *map, char **lines)
{
	int	i;

	map->height = get_lines(lines);
	map->width = get_max_line(lines);
	extract_map(game, map, lines);
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
