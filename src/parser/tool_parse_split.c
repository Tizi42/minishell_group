/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tool_parse_split.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tyuan <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/22 17:30:59 by tyuan             #+#    #+#             */
/*   Updated: 2021/10/22 17:32:00 by tyuan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**jump_quotes_ft_split(char const *s, char *quoted, char c)
{
	char	**tabs;
	int		ct[3];

	if (!s)
		return (NULL);
	ft_memset(ct, 0, sizeof(ct));
	tabs = v_malloc(sizeof(char *) * (sizec(s, c) + 2));
	ct[0] = -1;
	while (s[ct[1]])
	{
		if ((s[ct[1]] == c && quoted[ct[1]] == NQ) || s[ct[1] + 1] == '\0')
		{
			if (s[ct[1] + 1] == '\0' && s[ct[1]] != c)
				ct[1]++;
			if (ct[1] - ct[0] != 1)
				if (!(docp(tabs, s, ct)))
					return (NULL);
			ct[0] = ct[1];
		}
		if (s[ct[1]])
			ct[1]++;
	}
	tabs[ct[2]] = NULL;
	return (tabs);
}

int	docp(char **tabs, char const *s, int *ct)
{
	int	i;

	tabs[ct[2]] = v_malloc(sizeof(char) * (ct[1] - ct[0]));
	i = 0;
	while (ct[0] + 1 + i < ct[1])
	{
		tabs[ct[2]][i] = s[ct[0] + 1 + i];
		i++;
	}
	tabs[ct[2]][i] = '\0';
	ct[2]++;
	return (1);
}

int	sizec(char const *s, char c)
{
	int	i;

	i = 0;
	if (s == NULL)
		return (0);
	while (*s)
	{
		if (*s == c)
			i++;
		s++;
	}
	return (i);
}
