/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmorot <mmorot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 18:08:15 by garivo            #+#    #+#             */
/*   Updated: 2025/01/15 14:57:52 by mmorot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include "../libft/libft.h"
# include "types.h"
# include <../minilibx-linux/mlx.h>
# include "layer.h"
# include "draw.h"
# include <stdio.h>
# include "utils.h"

typedef struct t_parsing
{
	char			*map;
	int				width;
	int				height;
	int				player_x;
	int				player_y;
	t_dir			player_dir;
	t_layer_stack	*textures;
	t_pixel			floor;
	t_pixel			ceiling;
}	t_parsing;

int		parse(t_game *game, const char *path);
int		parse_map(t_parsing *map, char **lines);
int		check_map(t_parsing *map);
char	*get_line(t_parsing *map, size_t i);
int		check_extension(const char *path, const char *ext);
int		set_textures(t_game *game);
int		convert_parsing(t_game *game, t_parsing *map);
int		extract_textures(t_game *game, char *line);
int		parse_header(t_game *game, t_parsing *map, char **lines);
void	set_background(t_game *game, t_parsing map);
int		extract_pixel(char *line, t_pixel *pixel);
char	*skip_sp(char *line);
char	*skip_digits(char *line);
size_t	get_max_line(char **lines);
int		check_extension(const char *path, const char *ext);
int		get_dir(char c);
int		check_dir(t_parsing *map, char *cmap, size_t i, size_t j);

#endif