/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmorot <mmorot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 08:11:19 by mmorot            #+#    #+#             */
/*   Updated: 2023/11/14 08:33:31 by mmorot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	little_len;

	little_len = ft_strlen(little);
	if (little_len == 0)
		return ((char *)big);
	i = 0;
	while (big[i] != '\0' && i < len)
	{
		if (ft_strncmp(big + i, little, little_len) == 0)
		{
			if (i + little_len > len)
				return ((void *)0);
			return ((char *)(big + i));
		}
		i++;
	}
	return ((void *)0);
}
