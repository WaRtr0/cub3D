/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmorot <mmorot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 22:45:57 by mmorot            #+#    #+#             */
/*   Updated: 2024/03/08 04:10:34 by mmorot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strlen_gnl(char *str)
{
	size_t	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i] != '\0')
		i++;
	return (i);
}

int	ft_endl(char *s)
{
	int	i;

	i = 0;
	if (!s)
		return (0);
	while (s[i] != '\0')
	{
		if (s[i] == '\n')
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strjoin_gnl(char *s1, char *s2)
{
	size_t	i;
	size_t	j;
	char	*new;

	if (!s1)
	{
		s1 = malloc(sizeof(char) * 1);
		s1[0] = '\0';
	}
	if (!s1 || !s2)
		return (NULL);
	new = malloc (sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!new)
		return (NULL);
	i = -1;
	j = 0;
	if (s1)
		while (s1[++i])
			new[i] = s1[i];
	while (s2[j])
		new[i++] = s2[j++];
	new[ft_strlen(s1) + ft_strlen(s2)] = '\0';
	free(s1);
	return (new);
}

char	*ft_getline(char *line)
{
	char	*temp;
	int		i;

	i = 0;
	if (!line[i])
		return (NULL);
	while (line[i] != '\0' && line[i] != '\n')
		i++;
	temp = malloc(sizeof(char) * (i + 2));
	if (!temp)
		return (NULL);
	i = 0;
	while (line[i] != '\0' && line[i] != '\n')
	{
		temp[i] = line[i];
		i++;
	}
	if (line[i] == '\n')
	{
		temp[i] = line[i];
		i++;
	}
	temp[i] = '\0';
	return (temp);
}

char	*ft_restline(char *line)
{
	int		i;
	int		j;
	char	*saved;

	i = 0;
	while (line[i] && (line[i] != '\n'))
		i++;
	if (!line[i] || (line[i] == '\n' && line[i + 1] == '\0'))
	{
		free(line);
		return (NULL);
	}
	saved = (char *)malloc(sizeof(char) * (ft_strlen(line) - i + 1));
	if (!saved)
		return (NULL);
	i++;
	j = 0;
	while (line[i])
		saved[j++] = line[i++];
	saved[j] = '\0';
	free(line);
	return (saved);
}
