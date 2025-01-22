/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmorot <mmorot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 08:08:54 by mmorot            #+#    #+#             */
/*   Updated: 2025/01/22 17:51:26 by mmorot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_white_space(const char *nptr, long *i)
{
	int	sign;

	sign = 1;
	while (nptr[*i] == ' ' || (nptr[*i] >= 9 && nptr[*i] <= 13))
		(*i)++;
	if (nptr[*i] == '+' || nptr[*i] == '-')
	{
		if (nptr[*i] == '-')
			sign = -1;
		(*i)++;
	}
	return (sign);
}

int	ft_atoi(const char *nptr)
{
	long	res;
	int		sign;
	long	i;

	res = 0;
	i = 0;
	sign = ft_white_space(nptr, &i);
	while (ft_isdigit(nptr[i]))
	{
		if (res != ((res * 10) + (nptr[i] - '0')) / 10)
		{
			if (sign > 0)
				return (-1);
			return (0);
		}
		res = (res * 10) + (nptr[i] - '0');
		i++;
	}
	return (res * sign);
}
