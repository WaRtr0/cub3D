/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmorot <mmorot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 18:58:49 by mmorot            #+#    #+#             */
/*   Updated: 2024/03/06 22:49:03 by mmorot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	count_words(char const *s, char c)
{
	size_t	i;
	size_t	words;

	i = 0;
	words = 0;
	while (s[i])
	{
		while (s[i] && s[i] == c)
			i++;
		if (s[i])
			words++;
		while (s[i] && s[i] != c)
			i++;
	}
	return (words);
}

static char	*malloc_word(char const *s, char c)
{
	size_t	i;
	char	*word;

	i = 0;
	while (s[i] && s[i] != c)
		i++;
	if (i <= 0)
		return ((void *)0);
	word = malloc(sizeof(char) * (i + 1));
	if (!word)
		return ((void *)0);
	ft_strlcpy(word, s, i + 1);
	return (word);
}

static int	free_array(char **array, size_t size)
{
	size_t	i;

	i = 0;
	while (i < size && array[i])
	{
		free(array[i]);
		i++;
	}
	free(array);
	return (1);
}

static int	skip_split(char const *s, char c, int not)
{
	int	i;

	i = 0;
	if (not)
		while (s[i] && s[i] != c)
			i++;
	else
		while (s[i] && s[i] == c)
			i++;
	return (i);
}

char	**ft_split(char const *s, char c)
{
	char	**split;
	size_t	words;
	size_t	i;

	if (!s)
		return ((void *)0);
	words = count_words(s, c);
	split = malloc(sizeof(char *) * (words + 1));
	if (! split)
		return ((void *)0);
	i = 0;
	while (i < words)
	{
		s += skip_split(s, c, 0);
		if (*s)
		{
			split[i] = malloc_word(s, c);
			if (! split[i] && free_array(split, i))
				return ((void *)0);
			i++;
		}
		s += skip_split(s, c, 1);
	}
	split[i] = (void *)0;
	return (split);
}
