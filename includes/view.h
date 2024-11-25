/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   view.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: garivo <garivo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 16:12:26 by garivo            #+#    #+#             */
/*   Updated: 2024/11/24 20:45:35 by garivo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VIEW_H
# define VIEW_H

# include "layer.h"
# include "utils.h"

typedef struct s_view
{
	double	*distances;
	double	*percents;
	int		center;
	int		width;
	int		height;
	double	wall_height;
}	t_view;

int	create_view(t_game *game);

#endif