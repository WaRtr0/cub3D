/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_checks.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: garivo <garivo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/23 00:11:50 by garivo            #+#    #+#             */
/*   Updated: 2024/12/13 00:38:06 by garivo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	check_extension(const char *path , const char *ext)
{
	size_t	len;
	size_t	ext_len;
	size_t	i;

	len = ft_strlen(path);
	ext_len = ft_strlen(ext);
	if (len < ext_len)
		return (prerr("Error\nInvalid file extension\n"), 0);
	i = len - ext_len;
	if (ft_strncmp(path + i, ext, ext_len) != 0)
		return (prerr("Error\nInvalid file extension\n"), 0);
	return (1);
}

int	get_dir(char c)
{
	if (c == 'N')
		return (NORTH);
	else if (c == 'S')
		return (SOUTH);
	else if (c == 'E')
		return (EAST);
	else if (c == 'W')
		return (WEST);
	return (-1);
}

int	check_dir(t_parsing *map, char *cmap, size_t i, size_t j)
{
	static int	startpos = 0;

	if (cmap[j] == 'N' || cmap[j] == 'S' || cmap[j] == 'E'
		|| cmap[j] == 'W')
	{
		if (startpos++ != 0)
			return (prerr("Error\nMap contains more than one player\n"), 0);
		map->player_dir = get_dir(cmap[j]);
		map->player_x = j;
		map->player_y = i;
	}
	else
		return (prerr("Error\nInvalid char\n"), 0);
	return (1);
}

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
			if (!(cmap[j] == '0' || cmap[j] == '1' || cmap[j] == ' ' || cmap[j] == 'D')) //BONUS
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
	if (i == 0 || i == (unsigned int)map->height - 1 || j == 0 || j == (unsigned int)map->width - 1)
		if (cmap[j] != ' ' && cmap[j] != '1')
			return (0);
	return (1);
}

int	check_closure(t_parsing	*map, char *cmap, size_t i, size_t j)
{
	if ((cmap[j] == '0' || cmap[j] == 'N' || cmap[j] == 'S'
			|| cmap[j] == 'E' || cmap[j] == 'W')
		&& !(i == 0 || i == (unsigned int)map->height || j == 0 || j == (unsigned int)map->width - 1))
	{
		if (cmap[j - 1] == ' ' || cmap[j + 1] == ' '
			|| get_line(map, i - 1)[j] == ' ' || get_line(map, i + 1)[j] == ' ')
			return (0);
	}
	if (cmap[j] == 'D' && !(cmap[j - 1] == '1' && cmap[j + 1] == '1')
		&& !(get_line(map, i - 1)[j] == '1'
		&& get_line(map, i + 1)[j] == '1'))
		return (prerr("Error\nInvalid door position\n"), 0);	//BONUS	
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
