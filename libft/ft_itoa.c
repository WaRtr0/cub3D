/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmorot <mmorot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 18:57:54 by mmorot            #+#    #+#             */
/*   Updated: 2023/11/14 07:37:53 by mmorot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	num_len(int n)
{
	int	len;

	len = 0;
	if (n <= 0)
		len++;
	while (n)
	{
		n /= 10;
		len++;
	}
	return (len);
}

static char	*rev_char(char *str, long size)
{
	long	i;
	char	temp;

	i = 0;
	while (str[i] && i < size / 2)
	{
		temp = str[size - 1 - i];
		str[size - 1 - i] = str[i];
		str[i] = temp;
		i++;
	}
	return (str);
}

char	*ft_itoa(int n)
{
	char		*str;
	int			len;
	long int	nb;

	nb = (long int)n;
	len = num_len(n);
	str = ft_calloc(sizeof(char), len + 1);
	if (!str)
		return ((void *)0);
	if (n < 0)
		nb *= -1;
	while (nb >= 10)
	{
		(*str) = (nb % 10) + '0';
		str++;
		nb /= 10;
	}
	(*str) = (nb % 10) + '0';
	str++;
	if (n < 0)
	{
		*str = '-';
		str++;
	}
	return (rev_char(str - len, len));
}
