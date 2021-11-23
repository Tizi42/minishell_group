/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tool_parse.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tyuan <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/22 17:32:35 by tyuan             #+#    #+#             */
/*   Updated: 2021/10/22 17:32:37 by tyuan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	remove_substr(char **line, int sub_start, int sub_end)
{
	char	*tmp;

	if (!line || !*line || sub_end < sub_start)
		return ;
	tmp = *line;
	tmp[sub_start] = '\0';
	*line = sh_strjoin(tmp, &tmp[sub_end + 1]);
	free(tmp);
}

char	*combine_strings(char **tabs)
{
	char	*newl;
	int		len;
	int		j;

	len = 0;
	j = 0;
	while (tabs[j])
		len += ft_strlen(tabs[j++]);
	newl = v_malloc(sizeof(char) * (len + 1));
	*newl = '\0';
	j = 0;
	while (tabs[j])
		ft_strlcat(newl, tabs[j++], len + 1);
	return (newl);
}

void	str_idx_split(char *l, int *start, int *end, char **tabs)
{
	int	i;
	int	n;

	i = 0;
	n = 0;
	if (start[0] > 0)
		tabs[n++] = sh_substr(l, 0, start[0]);
	while (start[i] >= 0)
	{
		tabs[n++] = sh_substr(l, start[i], end[i] - start[i] + 1);
		if (l[end[i] + 1])
		{
			if (start[i + 1] > 0)
				tabs[n++] = sh_substr(l, end[i] + 1, start[i + 1] - end[i] - 1);
			else
				tabs[n++] = ft_strdup(&l[end[i] + 1]);
		}
		i++;
	}
	tabs[n] = NULL;
}

void	remove_substrs(char **l, char **q, int s, int e)
{
	remove_substr(l, s, e);
	remove_substr(q, s, e);
}
