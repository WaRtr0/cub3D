/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: garivo <garivo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 18:08:15 by garivo            #+#    #+#             */
/*   Updated: 2024/12/04 15:50:43 by garivo           ###   ########.fr       */
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
	NORTH,
	EAST,
	SOUTH,
	WEST
}	t_dir;

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
int		parse_map(t_game *game, t_parsing *map, char **lines);
int		check_map(t_parsing *map);
char	*get_line(t_parsing *map, size_t i);
int		check_extension(const char *path , const char *ext);

#endif