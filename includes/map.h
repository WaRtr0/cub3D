/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmorot <mmorot@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 00:20:26 by mmorot            #+#    #+#             */
/*   Updated: 2025/01/22 00:20:26 by mmorot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_H
# define MAP_H

# include "game.h"
# include "types.h"

void	yaw_init(t_game *game);
void	map_init(t_map *map_struct, t_game *game);
void	map_draw_init(t_game *game, t_layer *group, t_map *map_struct);

#endif