/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_textures.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: garivo <garivo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 18:03:06 by garivo            #+#    #+#             */
/*   Updated: 2025/01/13 19:12:01 by garivo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"


static int	door_textures(t_game *game)
{
	int			i;
	static char	path[] = "./assets/textures/c_dr0x.xpm";
	char		*id;

	i = 0;
	while (i < 37)
	{
		id = ft_itoa(i + 1);
		if (!id)
			return (0);
		if (i < 10)
			path[23] = id[0];
		else
		{
			path[22] = id[0];
			path[23] = id[1];
		}
		printf("%s\n", path);
		layer_add_texture(game->mlx, game->textures,
			path, D_FACE + i);
		if (!layer_stack_get(game->textures, D_FACE + i))
			return (free(id), 0);
		i++;
	}
	return (free(id), 1);
}

int	set_textures(t_game *game)
{
	if (!door_textures(game))
		return (0);
	layer_add_texture(game->mlx, game->textures,
		"./assets/textures/ceiling.xpm", CEILING_TEXTURE);
	if (!layer_stack_get(game->textures, CEILING_TEXTURE))
		return (0);
	return (1);
}
