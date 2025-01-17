/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_header.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: garivo <garivo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 19:18:47 by garivo            #+#    #+#             */
/*   Updated: 2025/01/17 19:16:33 by garivo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void	set_background(t_game *game, t_parsing map)
{
	t_layer				*background_split;
	t_layer				*group;
	const unsigned int	height = (OUTPUT_HEIGHT / RATIO);
	const unsigned int	width = (OUTPUT_WIDTH / RATIO);

	background_split = layer_create(game->mlx, width, height * 2, 1);
	layer_split_fill(background_split, map.ceiling, map.floor);
	layer_set_offset(background_split, 0, (-(height / 2)));
	group = layer_group_create(width, height, 1);
	layer_group_add(group, background_split);
	layer_stack_add(game->layers, group);
}

int	extract_background(t_parsing *map, char *line)
{
	t_pixel	ceiling;
	t_pixel	floor;

	if (*line == 'F')
	{
		if (map->floor.r != 277)
			return (prerr("Error\nFloor already declared\n"), 0);
		if (!extract_pixel(line, &floor))
			return (0);
		map->floor = floor;
	}
	else if (*line == 'C')
	{
		if (map->ceiling.r != 277)
			return (prerr("Error\nCeiling already declared\n"), 0);
		if (!extract_pixel(line, &ceiling))
			return (0);
		map->ceiling = ceiling;
	}
	return (1);
}

int	header_parsing(t_game *game, t_parsing *map, char **lines, size_t i)
{
	char	*line;

	while (lines[i])
	{
		line = lines[i];
		line = skip_sp(line);
		if (ft_strncmp(line, "NO", 2) == 0 || ft_strncmp(line, "SO", 2) == 0
			|| ft_strncmp(line, "WE", 2) == 0 || ft_strncmp(line, "EA", 2) == 0)
		{
			if (!extract_textures(game, line))
				return (0);
		}
		else if (*line == 'F' || *line == 'C')
		{
			if (!extract_background(map, line))
				return (0);
		}
		else if (*line == '1' || *line == '0' || *line == ' '
			|| *line == 'N' || *line == 'S' || *line == 'E' || *line == 'W')
			break ;
		else if (*line != '\0')
			return (prerr("Error\nInvalid character in header\n"), 0);
		i++;
	}
	return (i);
}

int	parse_header(t_game *game, t_parsing *map, char **lines)
{
	size_t	i;

	i = header_parsing(game, map, lines, 0);
	if (!i)
		return (0);
	if (!layer_stack_get(game->textures, N_FACE)
		|| !layer_stack_get(game->textures, E_FACE)
		|| !layer_stack_get(game->textures, S_FACE)
		|| !layer_stack_get(game->textures, W_FACE)
		|| map->floor.r == 277 || map->ceiling.r == 277)
		return (prerr("Error\nMissing element in header\n"), 0);
	return (i);
}
