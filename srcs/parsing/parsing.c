/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: garivo <garivo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 18:10:06 by garivo            #+#    #+#             */
/*   Updated: 2025/01/17 18:06:29 by garivo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include <stdio.h>

size_t	get_lenght(int fd)
{
	size_t	n;
	char	*line;

	n = 0;
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		free(line);
		n++;
	}
	return (n);
}

char	**extract_all(const char *path)
{
	int		fd;
	char	**lines;
	size_t	i;
	size_t	lenght;

	fd = open(path, O_RDONLY);
	if (fd < 0)
		return (prerr("Error\nFailed to open the map file\n"), NULL);
	lenght = get_lenght(fd);
	close(fd);
	fd = open(path, O_RDONLY);
	lines = malloc(sizeof(char *) * (lenght + 1));
	if (!lines)
		return (NULL);
	i = 0;
	while (1)
	{
		lines[i] = get_next_line(fd);
		if (!lines[i])
			break ;
		if (lines[i][ft_strlen(lines[i]) - 1] == '\n')
			lines[i][ft_strlen(lines[i]) - 1] = '\0';
		i++;
	}
	return (close(fd), lines);
}

static int	free_lines(char **lines)
{
	size_t	i;

	i = 0;
	while (lines[i])
	{
		free(lines[i]);
		i++;
	}
	free(lines);
	return (0);
}

static int	destroy_parsing(t_parsing *map)
{
	if (map->map)
		free(map->map);
	return (0);
}

int	parse(t_game *game, const char *path)
{
	char		**lines;
	t_parsing	map;
	int			end_of_header;

	ft_memset(&map, 0, sizeof(t_parsing));
	map.player_dir = -1;
	map.floor.r = 277;
	map.ceiling.r = 277;
	if (!check_extension(path, ".cub"))
		return (destroy_parsing(&map));
	lines = extract_all(path);
	if (!lines)
		return (destroy_parsing(&map));
	end_of_header = parse_header(game, &map, lines);
	if (!end_of_header)
		return (free_lines(lines), destroy_parsing(&map));
	if (!parse_map(&map, lines + end_of_header))
		return (free_lines(lines), destroy_parsing(&map));
	free_lines(lines);
	if (!set_textures(game))
		return (destroy_parsing(&map));
	if (!convert_parsing(game, &map))
		return (destroy_parsing(&map));
	free(map.map);
	return (set_background(game, map), 1);
}
