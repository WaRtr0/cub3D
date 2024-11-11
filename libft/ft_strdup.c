/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmorot <mmorot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 08:06:58 by mmorot            #+#    #+#             */
/*   Updated: 2023/11/14 08:33:38 by mmorot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	int		len;
	char	*copy;

	len = ft_strlen(s) + 1;
	copy = (char *)malloc(sizeof(char) * len);
	if (!copy)
		return ((void *)0);
	ft_memcpy(copy, s, len);
	return (copy);
}
