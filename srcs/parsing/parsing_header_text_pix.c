/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_header_text_pix.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: garivo <garivo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 19:22:09 by garivo            #+#    #+#             */
/*   Updated: 2025/01/17 19:01:50 by garivo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

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
	if (pixel->r > 255 || pixel->g > 255
		|| pixel->b > 255)
		return (prerr("Error\nRGB values must be between 0 and 255\n"), 0);
	return (1);
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
