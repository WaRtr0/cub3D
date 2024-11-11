/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmorot <mmorot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 08:22:00 by mmorot            #+#    #+#             */
/*   Updated: 2023/11/14 08:33:36 by mmorot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*join;
	size_t	s1_len;
	size_t	s2_len;

	if (!s1 && !s2)
		return ((void *)0);
	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	join = malloc(sizeof(char) * (s1_len + s2_len + 1));
	if (!join)
		return ((void *)0);
	ft_strlcpy(join, s1, s1_len + 1);
	ft_strlcat(join, s2, s1_len + s2_len + 1);
	return (join);
}
