/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tool_str.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tyuan <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/29 16:56:21 by tyuan             #+#    #+#             */
/*   Updated: 2021/10/29 16:56:36 by tyuan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*sh_substr(char const *s, unsigned int start, size_t len)
{
	char	*ext;
	size_t	i;

	if (s == NULL)
		return (NULL);
	if (ft_strlen(s) < start)
		return (ft_strdup(""));
	ext = v_malloc(len + 1);
	i = 0;
	while (s[start + i] && i < len)
	{
		ext[i] = s[start + i];
		i++;
	}
	ext[i] = '\0';
	return (ext);
}

char	*sh_strjoin(char const *s1, char const *s2)
{
	char	*a;
	size_t	t1;
	size_t	t2;

	t1 = 0;
	t2 = 0;
	a = v_malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	while (s1 && s1[t1])
	{
		a[t1] = s1[t1];
		t1++;
	}
	while (s2 && s2[t2])
	{
		a[t1 + t2] = s2[t2];
		t2++;
	}
	a[t1 + t2] = '\0';
	return (a);
}

int	str_start_with(const char *line, char c)
{
	while (*line && *line == ' ')
		line++;
	if (*line == c)
		return (1);
	else
		return (0);
}

int	str_end_with(const char *line, char c)
{
	int	n;

	n = ft_strlen(line) - 1;
	while (n > 0 && line[n] == ' ')
		n--;
	if (line[n] == c)
		return (1);
	else
		return (0);
}

char	*str_quote_removal(char *str)
{
	t_token	*tok;
	char	*ret;

	tok = new_token(WORD, str, set_quoted_bits(str));
	quote_removal(tok, NULL);
	ret = ft_strdup(tok->word);
	clean_token(tok);
	return (ret);
}
