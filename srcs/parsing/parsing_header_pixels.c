/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_header_pixels.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmorot <mmorot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 19:22:09 by garivo            #+#    #+#             */
/*   Updated: 2025/01/22 18:03:48 by mmorot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

char	*skip_digits(char *line)
{
	while (*line >= '0' && *line <= '9')
		line++;
	return (line);
}

int	check_pixel(t_pixel *pixel)
{
	if (pixel->r > 255 || pixel->g > 255
		|| pixel->b > 255)
		return (prerr("Error\nRGB values must be between 0 and 255\n"), 0);
	return (1);
}

int	extract_pixel(char *line, t_pixel *pixel)
{
	line = skip_sp(line + 1);
	if (!ft_isdigit(*line))
		return (prerr("Error\nInvalid RGB declaration (digits expected)\n"), 0);
	pixel->r = ft_atoi(line);
	line = skip_digits(line);
	if (*line != ',')
		return (prerr("Error\nRGB values must be comma separated\n"), 0);
	line = skip_sp(++line);
	if (!ft_isdigit(*line))
		return (prerr("Error\nInvalid RGB declaration (digits expected)\n"), 0);
	pixel->g = ft_atoi(line);
	line = skip_digits(line);
	if (*line != ',')
		return (prerr("Error\nRGB values must be comma separated\n"), 0);
	line = skip_sp(++line);
	if (!ft_isdigit(*line))
		return (prerr("Error\nInvalid RGB declaration (digits expected)\n"), 0);
	pixel->b = ft_atoi(line);
	line = skip_digits(line);
	line = skip_sp(line);
	if (*line != '\0')
		return (prerr("Error\nInvalid character after RGB declaration\n"), 0);
	pixel->a = 255;
	return (check_pixel(pixel));
}
