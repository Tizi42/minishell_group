/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkromer <jkromer@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/19 12:30:07 by jkromer           #+#    #+#             */
/*   Updated: 2021/01/20 00:07:02 by jkromer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

static size_t	count_words(const char *s, const char *sep)
{
	int	nb_words;
	int	i;
	int	is_word;

	nb_words = 0;
	i = 0;
	is_word = 0;
	while (s[i])
	{
		if (!is_sep(s[i], sep))
			is_word = 1;
		else if (is_sep(s[i], sep) && is_word)
		{
			nb_words++;
			is_word = 0;
		}
		i++;
	}
	if (is_word)
		nb_words++;
	return (nb_words);
}

static size_t	get_word_len(const char *s, const char *sep)
{
	int	i;

	i = 0;
	while (!is_sep(s[i], sep) && s[i])
		i++;
	return (i);
}

static void	free_tab(char **split, int j)
{
	while (j)
		free(split[j--]);
	free(split[j]);
	free(split);
}

static int	check_null(char **split, int j)
{
	if (!split[j])
	{
		free_tab(split, j);
		return (1);
	}
	return (0);
}

char	**ft_split(char const *s, const char *sep)
{
	char	**split;
	int		nb_words;
	int		i;
	int		j;
	int		word_len;

	nb_words = count_words(s, sep);
	split = malloc(sizeof(char *) * (nb_words + 1));
	if (!split)
		return (NULL);
	i = 0;
	j = 0;
	while (j < nb_words && s[i])
	{
		word_len = get_word_len(s + i, sep);
		if (word_len)
		{
			split[j++] = ft_substr(s, i, word_len);
			if (check_null(split, j - 1))
				return (NULL);
		}
		i += word_len + 1;
	}
	split[nb_words] = 0;
	return (split);
}
