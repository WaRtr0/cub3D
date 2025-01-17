/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_checks_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: garivo <garivo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 19:56:07 by garivo            #+#    #+#             */
/*   Updated: 2025/01/17 19:41:36 by garivo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	check_extension(const char *path, const char *ext)
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

	if (map == NULL)
		return (startpos);
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
