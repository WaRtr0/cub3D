/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: garivo <garivo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 18:08:15 by garivo            #+#    #+#             */
/*   Updated: 2024/11/24 20:45:21 by garivo           ###   ########.fr       */
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

typedef enum e_dir 
{
	N,
	S,
	E,
	W
}	t_dir;

typedef struct s_map
{
	char	*map;
	int		width;
	int		height;
	int		player_x;
	int		player_y;
	t_dir	player_dir;
	t_img	n;
	t_img	s;
	t_img	e;
	t_img	w;
	t_pixel	floor;
	t_pixel	ceiling;
}	t_map;


int		parse(t_game *game, const char *path);
int		parse_map(t_game *game, t_map *map, char **lines);
int		check_map(t_map *map);
char	*get_line(t_map *map, size_t i);

#endif