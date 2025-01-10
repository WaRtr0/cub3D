/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gladius <gladius@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 18:10:06 by garivo            #+#    #+#             */
/*   Updated: 2025/01/09 22:20:44 by gladius          ###   ########.fr       */
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
	close(fd);
	return (lines);
}

char	*skip_sp(char *line)
{
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

int	extract_textures(t_game *game, char *line)
{
	char	*path;
	t_face	dir;

	path = extract_last_word(skip_sp(line + 2));
	dir = 0;
	if (!path || !check_extension(path, ".xpm"))
		return (0);
	if (ft_strncmp(line, "NO", 2) == 0)
		dir = N_FACE;
	else if (ft_strncmp(line, "SO", 2) == 0)
		dir = S_FACE;
	else if (ft_strncmp(line, "WE", 2) == 0)
		dir = W_FACE;
	else if (ft_strncmp(line, "EA", 2) == 0)
		dir = E_FACE;
	if (layer_stack_get(game->textures, dir))
		return (prerr("Error\nTexture already declared\n"), 0);
	layer_add_texture(game->mlx, game->textures, path, dir);
	if (!layer_stack_get(game->textures, dir))
		return (prerr("Error\nFailed to load texture\n"), 0);
	return (1);
}

int	extract_pixel(char *line, t_pixel *pixel)
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
	if ( pixel->r > 255 || pixel->g > 255
		|| pixel->b > 255)
		return (prerr("Error\nRGB values must be between 0 and 255\n"), 0);
	return (1);
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
	if (!layer_stack_get(game->textures, N_FACE)
		|| !layer_stack_get(game->textures, E_FACE)
		|| !layer_stack_get(game->textures, S_FACE)
		|| !layer_stack_get(game->textures, W_FACE)
		|| map->floor.r == 277 || map->ceiling.r == 277)
		return (prerr("Error\nMissing element in header\n"), 0);
	return (i);
}

int	convert_parsing(t_game *game, t_parsing *map)
{
	t_map_tile	*tiles;
	size_t		i;
	size_t		offset;

	game->data->map = malloc(sizeof(t_map));
	if (!game->data->map)
		return (0);
	game->data->player.x = map->player_x;
	game->data->player.y = map->player_y;
	game->data->yaw = map->player_dir * 90;
	game->data->map->tiles = NULL;
	//game->data->yaw = map->player_dir; uh?
	game->data->map->height = map->height;
	game->data->map->width = map->width;
	tiles = malloc(sizeof(t_map_tile) * map->height * (map->width + 1));
	if (!tiles)
		return (0);
	i = 0;
	offset = 0;
	while (i + offset < (unsigned int)(map->height * (map->width + 1)))
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
			tiles[i] = D;
		i++;
	}
	tiles[i] = '\0';
	game->data->map->tiles = tiles;
	return (1);
}

int	set_textures(t_game *game)
{
	int i;

	i = 1;
	layer_add_texture(game->mlx, game->textures,
		"./assets/textures/c_dr1.xpm", D_FACE);
	if (!layer_stack_get(game->textures, D_FACE))
		return (0);
	layer_add_texture(game->mlx, game->textures,
		"./assets/textures/c_dr2.xpm", D_FACE + i);
	if (!layer_stack_get(game->textures, D_FACE + i++))
		return (0);
	layer_add_texture(game->mlx, game->textures,
		"./assets/textures/c_dr3.xpm", D_FACE + i);
	if (!layer_stack_get(game->textures, D_FACE + i++))
		return (0);
	layer_add_texture(game->mlx, game->textures,
		"./assets/textures/c_dr4.xpm", D_FACE + i);
	if (!layer_stack_get(game->textures, D_FACE + i++))
		return (0);
	layer_add_texture(game->mlx, game->textures,
		"./assets/textures/c_dr5.xpm", D_FACE + i);
	if (!layer_stack_get(game->textures, D_FACE + i++))
		return (0);
	layer_add_texture(game->mlx, game->textures,
		"./assets/textures/c_ NULL;dr6.xpm", D_FACE + i);
	if (!layer_stack_get(game->textures, D_FACE + i++))
		return (0);
	layer_add_texture(game->mlx, game->textures,
		"./assets/textures/c_dr7.xpm", D_FACE + i);
	if (!layer_stack_get(game->textures, D_FACE + i++))
		return (0);
	layer_add_texture(game->mlx, game->textures,
		"./assets/textures/c_dr8.xpm", D_FACE + i);
	if (!layer_stack_get(game->textures, D_FACE + i++))
		return (0);
	layer_add_texture(game->mlx, game->textures,
		"./assets/textures/c_dr9.xpm", D_FACE + i);
	if (!layer_stack_get(game->textures, D_FACE + i++))
		return (0);
	layer_add_texture(game->mlx, game->textures,
		"./assets/textures/c_dr10.xpm", D_FACE + i);
	if (!layer_stack_get(game->textures, D_FACE + i++))
		return (0);
	layer_add_texture(game->mlx, game->textures,
		"./assets/textures/c_dr11.xpm", D_FACE + i);
	if (!layer_stack_get(game->textures, D_FACE + i++))
		return (0);
	layer_add_texture(game->mlx, game->textures,
		"./assets/textures/c_dr12.xpm", D_FACE + i);
	if (!layer_stack_get(game->textures, D_FACE + i++))
		return (0);
	layer_add_texture(game->mlx, game->textures,
		"./assets/textures/c_dr13.xpm", D_FACE + i);
	if (!layer_stack_get(game->textures, D_FACE + i++))
		return (0);
	layer_add_texture(game->mlx, game->textures,
		"./assets/textures/c_dr14.xpm", D_FACE + i);
	if (!layer_stack_get(game->textures, D_FACE + i++))
		return (0);
	layer_add_texture(game->mlx, game->textures,
		"./assets/textures/c_dr15.xpm", D_FACE + i);
	if (!layer_stack_get(game->textures, D_FACE + i++))
		return (0);
	layer_add_texture(game->mlx, game->textures,
		"./assets/textures/c_dr16.xpm", D_FACE + i);
	if (!layer_stack_get(game->textures, D_FACE + i++))
		return (0);
	layer_add_texture(game->mlx, game->textures,
		"./assets/textures/c_dr17.xpm", D_FACE + i);
	if (!layer_stack_get(game->textures, D_FACE + i++))
		return (0);
	layer_add_texture(game->mlx, game->textures,
		"./assets/textures/c_dr18.xpm", D_FACE + i);
	if (!layer_stack_get(game->textures, D_FACE + i++))
		return (0);
	layer_add_texture(game->mlx, game->textures,
		"./assets/textures/c_dr19.xpm", D_FACE + i);
	if (!layer_stack_get(game->textures, D_FACE + i++))
		return (0);
	layer_add_texture(game->mlx, game->textures,
		"./assets/textures/c_dr20.xpm", D_FACE + i);
	if (!layer_stack_get(game->textures, D_FACE + i++))
		return (0);
	layer_add_texture(game->mlx, game->textures,
		"./assets/textures/c_dr21.xpm", D_FACE + i);
	if (!layer_stack_get(game->textures, D_FACE + i++))
		return (0);
	layer_add_texture(game->mlx, game->textures,
		"./assets/textures/c_dr22.xpm", D_FACE + i);
	if (!layer_stack_get(game->textures, D_FACE + i++))
		return (0);
	layer_add_texture(game->mlx, game->textures,
		"./assets/textures/c_dr23.xpm", D_FACE + i);
	if (!layer_stack_get(game->textures, D_FACE + i++))
		return (0);
	layer_add_texture(game->mlx, game->textures,
		"./assets/textures/c_dr24.xpm", D_FACE + i);
	if (!layer_stack_get(game->textures, D_FACE + i++))
		return (0);
	layer_add_texture(game->mlx, game->textures,
		"./assets/textures/c_dr25.xpm", D_FACE + i);
	if (!layer_stack_get(game->textures, D_FACE + i++))
		return (0);
	layer_add_texture(game->mlx, game->textures,
		"./assets/textures/c_dr26.xpm", D_FACE + i);
	if (!layer_stack_get(game->textures, D_FACE + i++))
		return (0);
	layer_add_texture(game->mlx, game->textures,
		"./assets/textures/c_dr27.xpm", D_FACE + i);
	if (!layer_stack_get(game->textures, D_FACE + i++))
		return (0);
	layer_add_texture(game->mlx, game->textures,
		"./assets/textures/c_dr28.xpm", D_FACE + i);
	if (!layer_stack_get(game->textures, D_FACE + i++))
		return (0);
	layer_add_texture(game->mlx, game->textures,
		"./assets/textures/c_dr29.xpm", D_FACE + i);
	if (!layer_stack_get(game->textures, D_FACE + i++))
		return (0);
	layer_add_texture(game->mlx, game->textures,
		"./assets/textures/c_dr30.xpm", D_FACE + i);
	if (!layer_stack_get(game->textures, D_FACE + i++))
		return (0);
	layer_add_texture(game->mlx, game->textures,
		"./assets/textures/c_dr31.xpm", D_FACE + i);
	if (!layer_stack_get(game->textures, D_FACE + i++))
		return (0);
	layer_add_texture(game->mlx, game->textures,
		"./assets/textures/c_dr32.xpm", D_FACE + i);
	if (!layer_stack_get(game->textures, D_FACE + i++))
		return (0);
	layer_add_texture(game->mlx, game->textures,
		"./assets/textures/c_dr33.xpm", D_FACE + i);
	if (!layer_stack_get(game->textures, D_FACE + i++))
		return (0);
	layer_add_texture(game->mlx, game->textures,
		"./assets/textures/c_dr34.xpm", D_FACE + i);
	if (!layer_stack_get(game->textures, D_FACE + i++))
		return (0);
	layer_add_texture(game->mlx, game->textures,
		"./assets/textures/c_dr35.xpm", D_FACE + i);
	if (!layer_stack_get(game->textures, D_FACE + i++))
		return (0);
	layer_add_texture(game->mlx, game->textures,
		"./assets/textures/c_dr36.xpm", D_FACE + i);
	if (!layer_stack_get(game->textures, D_FACE + i++))
		return (0);
	layer_add_texture(game->mlx, game->textures,
		"./assets/textures/c_dr37.xpm", D_FACE + i);
	if (!layer_stack_get(game->textures, D_FACE + i++))
		return (0);

	layer_add_texture(game->mlx, game->textures,
		"./assets/textures/floor.xpm", FLOOR_TEXTURE);
	if (!layer_stack_get(game->textures,FLOOR_TEXTURE))
		return (0);

	layer_add_texture(game->mlx, game->textures,
		"./assets/textures/ceiling.xpm", CEILING_TEXTURE);
	if (!layer_stack_get(game->textures,CEILING_TEXTURE))
		return (0);

	return (1);
}

static int free_lines(char **lines)
{
	size_t i;

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
	t_layer		*background_split;
	t_layer		*group;

	ft_memset(&map, 0, sizeof(t_parsing));
	map.player_dir = -1;
	map.floor.r = 277;
	map.ceiling.r = 277;
	if (!check_extension(path, ".cub"))
		return (destroy_parsing(&map));
	if (!set_textures(game))
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
	if (!convert_parsing(game, &map))
		return (destroy_parsing(&map));
	free(map.map);
	background_split = layer_create(game->mlx, WIDTH, HEIGHT * 2, 1);
	layer_split_fill(background_split, map.ceiling, map.floor);
	layer_set_offset(background_split, 0, SPLIT_HEIGHT);
	group = layer_group_create(WIDTH, HEIGHT, 1);
	layer_group_add(group, background_split);
	layer_stack_add(game->layers, group);
	return (1);
}

//free la map