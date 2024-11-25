/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: garivo <garivo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 18:10:06 by garivo            #+#    #+#             */
/*   Updated: 2024/11/24 21:47:05 by garivo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

t_img	init_img(t_img *img_data, void *img, int x, int y)
{
	img_data->img = img;
	if (!img)
		return (*img_data);
	img_data->w = x;
	img_data->h = y;
	img_data->addr = mlx_get_data_addr(img_data->img, &img_data->bpp,
			&img_data->line_len, &img_data->endian); //A voir si on doit securiser
	return (*img_data);
}

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
	lenght = get_lenght(fd);
	close(fd);
	fd = open(path, O_RDONLY);
	lines = malloc(sizeof(char *) * (lenght + 1));
	if (!lines)
		return (0);
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

int	extract_textures(t_game *game, t_map *map, char *line)
{
	int		x;
	int		y;
	void	*img;

	img = mlx_xpm_file_to_image(game->mlx, skip_sp(line + 2), &x, &y);
	if (!img)
		return (0);
	x = 0;
	y = 0;
	if (ft_strncmp(line, "NO", 2) == 0)
	{
		if (!init_img(&map->n, img, x, y).addr)
			return (mlx_destroy_image(game->mlx, img), 0);
	}
	else if (ft_strncmp(line, "SO", 2) == 0)
	{
		if (!init_img(&map->s, img, x, y).addr)
			return (mlx_destroy_image(game->mlx, img), 0);
	}
	else if (ft_strncmp(line, "WE", 2) == 0)
	{
		if (!init_img(&map->w, img, x, y).addr)
			return (mlx_destroy_image(game->mlx, img), 0);
	}
	else if (ft_strncmp(line, "EA", 2) == 0)
	{
		if (!init_img(&map->e, img, x, y).addr)
			return (mlx_destroy_image(game->mlx, img), 0);
	}
	else
		return (mlx_destroy_image(game->mlx, img), 0);
	return (1);
}

int	extract_pixel(t_game *game, t_map *map, char *line, t_pixel *pixel)
{
	//ft_memset(&pixel, 0, sizeof(t_pixel)); Heuuu
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
	return (1);
}

int	extract_background(t_game *game, t_map *map, char *line)
{
	t_pixel	ceiling;
	t_pixel	floor;

	if (*line == 'F')
	{
		if (!extract_pixel(game, map, line, &floor))
			return (0);
		map->floor = floor;
	}
	else if (*line == 'C')
	{
		if (!extract_pixel(game, map, line, &ceiling))
			return (0);
		map->ceiling = ceiling;
	}
	return (1);
}



int	parse_header(t_game *game, t_map *map, char **lines)
{
	size_t	i;
	char	*line;

	i = 0;
	while (lines[i])
	{
		line = lines[i];
		line = skip_sp(line);
		if (ft_strncmp(line, "NO", 2) == 0
			|| ft_strncmp(line, "SO", 2) == 0
			|| ft_strncmp(line, "WE", 2) == 0
			|| ft_strncmp(line, "EA", 2) == 0)
		{
			if (!extract_textures(game, map, line))
				return (0);
		}
		else if (*line == 'F' || *line == 'C')
		{
			if (!extract_background(game, map, line))
				return (0);
		}
		else if (*line != '\0')
			break ;
		i++;
	}
	return (i);
}

int	parse(t_game *game, const char *path)
{
	char	**lines;
	size_t	i;
	t_map	map;
	int		end_of_header;

	ft_memset(&map, 0, sizeof(t_map));
	map.player_dir = -1;
	lines = extract_all(path);
	if (!lines)
		return (0);
	end_of_header = parse_header(game, &map, lines);
	printf("\nEnd of header : %i\n", end_of_header);
	printf("NO: %s\n", map.n.addr);
	printf("SO: %s\n", map.s.addr);
	printf("WE: %s\n", map.w.addr);
	printf("EA: %s\n", map.e.addr);
	printf("F: %d %d %d %d\n", map.floor.r, map.floor.g, map.floor.b, map.floor.a);
	printf("C: %d %d %d %d\n", map.ceiling.r, map.ceiling.g, map.ceiling.b, map.ceiling.a);	
	parse_map(game, &map, lines + end_of_header);
	i = 0;
	while (lines[i])
	{
		free(lines[i]);
		i++;
	}
	free(lines);
	
	return (1);
}
