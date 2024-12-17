/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: garivo <garivo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 18:10:06 by garivo            #+#    #+#             */
/*   Updated: 2024/12/17 23:36:47 by garivo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

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
	return (lines);
}

char	*skip_sp(char *line)
{
	int	i;
	while (*line == ' ')
		line++;
	return (line);
}

char	*skip_digits(char *line)
{
	while (*line >= '0' && *line <= '9')
		line++;
	return (line);
}

char	*extract_last_word(char *line)
{
	size_t	i;
	size_t	word_end;

	i = 0;
	if (!line[i])
		return (prerr("Error\nEmpty texture declaration\n"), NULL);
	while (line[i] && line[i] != ' ')
		i++;
	word_end = i;
	while (line[i] && line[i] == ' ')
		i++;
	if (line[i] != '\0')
		return (prerr("Error\nInvalid character after texture declaration\n"),
			NULL);
	else
		line[word_end] = '\0';
	return (line);
}

int	extract_textures(t_game *game, t_parsing *map, char *line)
{
	void	*img;
	char	*path;
	t_dir	dir;

	path = extract_last_word(skip_sp(line + 2));
	if (!path || !check_extension(path, ".xpm"))
		return (0);
	if (ft_strncmp(line, "NO", 2) == 0)
		dir = NORTH;
	else if (ft_strncmp(line, "SO", 2) == 0)
		dir = SOUTH;
	else if (ft_strncmp(line, "WE", 2) == 0)
		dir = WEST;
	else if (ft_strncmp(line, "EA", 2) == 0)
		dir = EAST;
	if (layer_stack_get(game->textures, dir))
		return (prerr("Error\nTexture already declared\n"), 0);
	layer_add_texture(game->mlx, game->textures, path, dir);
	if (!layer_stack_get(game->textures, dir))
		return (0);
	return (1);
}

int	extract_pixel(t_game *game, t_parsing *map, char *line, t_pixel *pixel)
{
	line = skip_sp(line + 1);
	pixel->r = ft_atoi(line);
	line = skip_digits(line);
	if (*line != ',')
		return (prerr("Error\nRGB values must be comma separated\n"), 0);
	line = skip_sp(++line);
	pixel->g = ft_atoi(line);
	line = skip_digits(line);
	if (*line != ',')
		return (prerr("Error\nRGB values must be comma separated\n"), 0);
	line = skip_sp(++line);
	pixel->b = ft_atoi(line);
	line = skip_digits(line);
	line = skip_sp(line);
	if (*line != '\0')
		return (prerr("Error\nInvalid character after RGB declaration\n"), 0);
	pixel->a = 255;
	if (pixel->r < 0 || pixel->r > 255 || pixel->g < 0 || pixel->g > 255
		|| pixel->b < 0 || pixel->b > 255)
		return (prerr("Error\nRGB values must be between 0 and 255\n"), 0);
	return (1);
}

int	extract_background(t_game *game, t_parsing *map, char *line)
{
	t_pixel	ceiling;
	t_pixel	floor;

	if (*line == 'F')
	{
		if (map->floor.r != -1)
			return (prerr("Error\nFloor color already declared\n"), 0);
		if (!extract_pixel(game, map, line, &floor))
			return (0);
		map->floor = floor;
	}
	else if (*line == 'C')
	{
		if (map->ceiling.r != -1)
			return (prerr("Error\nCeiling color already declared\n"), 0);
		if (!extract_pixel(game, map, line, &ceiling))
			return (0);
		map->ceiling = ceiling;
	}
	return (1);
}



int	parse_header(t_game *game, t_parsing *map, char **lines)
{
	size_t	i;
	char	*line;

	i = 0;
	while (lines[i])
	{
		line = lines[i];
		line = skip_sp(line);
		if (ft_strncmp(line, "NO", 2) == 0 || ft_strncmp(line, "SO", 2) == 0
			|| ft_strncmp(line, "WE", 2) == 0 || ft_strncmp(line, "EA", 2) == 0)
		{
			if (!extract_textures(game, map, line))
				return (0);
		}
		else if (*line == 'F' || *line == 'C')
		{
			if (!extract_background(game, map, line))
				return (0);
		}
		else if (*line == '1' || *line == '0' || *line == ' '
			|| *line == 'N' || *line == 'S' || *line == 'E' || *line == 'W')
			break ;
		else if (*line != '\0')
			return (prerr("Error\nInvalid character in header\n"), 0);
		i++;
	}
	if (!layer_stack_get(game->textures, NORTH)
		|| !layer_stack_get(game->textures, EAST)
		|| !layer_stack_get(game->textures, SOUTH)
		|| !layer_stack_get(game->textures, WEST)
		|| map->floor.r == -1 || map->ceiling.r == -1)
		return (prerr("Error\nMissing element in header\n"), 0);
	return (i);
}

int	convert_parsing(t_game *game, t_parsing *map)
{
	t_map_tile	*tiles;
	size_t		i;
	size_t		offset;

	game->data->player.x = map->player_x;
	game->data->player.y = map->player_y;
	game->data->map = malloc(sizeof(t_map));
	if (!game->data->map)
		return (0);
	game->data->yaw = map->player_dir * 90;
	printf("Player dir: %f\n", game->data->yaw);
	game->data->map->height = map->height;
	game->data->map->width = map->width;
	tiles = malloc(sizeof(t_map_tile) * map->height * (map->width + 1));
	if (!tiles)
		return (free(game->data->map), 0);
	i = 0;
	offset = 0;
	while (i + offset < map->height * (map->width + 1))
	{
		if (map->map[i + offset] == 'N')
			tiles[i] = P;
		else if (map->map[i + offset] == 'S')
			tiles[i] = P;
		else if (map->map[i + offset] == 'E')
			tiles[i] = P;
		else if (map->map[i + offset] == 'W')
			tiles[i] = P;
		else if (map->map[i + offset] == '1')
			tiles[i] = W;
		else if (map->map[i + offset] == '0' || map->map[i + offset] == ' ')
			tiles[i] = E;
		else if (map->map[i + offset] == '\0' && i--)
			offset++;
		else if (map->map[i + offset] == 'D')
			tiles[i] = E;
		i++;
	}
	tiles[i] = '\0';
	game->data->map->tiles = tiles;
	return (1);
}

int	parse(t_game *game, const char *path)
{
	char		**lines;
	size_t		i;
	t_parsing	map;
	int			end_of_header;
	t_layer		*background_split;
	t_layer		*group;

	ft_memset(&map, 0, sizeof(t_parsing));
	map.player_dir = -1;
	map.floor.r = -1;
	map.ceiling.r = -1;
	if (!check_extension(path, ".cub"))
		return (0);
	lines = extract_all(path);
	if (!lines)
		return (0);
	end_of_header = parse_header(game, &map, lines);
	if (!end_of_header)
		return (0);
	if (!parse_map(game, &map, lines + end_of_header))
		return (0);
	i = 0;
	while (lines[i])
	{
		free(lines[i]);
		i++;
	}
	free(lines);
	if (!convert_parsing(game, &map))
		return (0);
	free(map.map);
	background_split = layer_create(game->mlx, WIDTH, HEIGHT * 2, 1);
    layer_split_fill(background_split, map.ceiling, map.floor);
    layer_set_offset(background_split, 0, SPLIT_HEIGHT);
	group = layer_group_create(WIDTH, HEIGHT, 1);
    layer_group_add(group, background_split);
    layer_stack_add(game->layers, group);
	return (1);
}

//free la map les pixels et les textures en cas d'erreur