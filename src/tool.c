/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tool.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tyuan <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/29 17:03:44 by tyuan             #+#    #+#             */
/*   Updated: 2021/11/26 12:16:22 by jkromer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	*v_malloc(size_t size)
{
	void	*ret;

	ret = malloc(size);
	if (!ret)
		unix_error("Malloc error");
	return (ret);
}

pid_t	v_fork(void)
{
	pid_t	pid;

	pid = fork();
	if (pid < 0)
		unix_error("Fork error");
	return (pid);
}

char	*get_env_value(char *key, t_exec exec)
{
	t_list	*cur;

	if (*key == '?')
		return (ft_itoa(exec.status));
	cur = exec.env;
	while (cur)
	{
		if (match_name(key, cur->c) == 1)
			return (ft_strdup(ft_strchr(cur->c, '=') + 1));
		cur = cur->n;
	}
	return (ft_strdup(NULL));
}

int	str_contains_set(const char *str, const char *set)
{
	if (!set)
		return (0);
	while (*set)
	{
		if (ft_contains(str, *set))
			return (1);
		set++;
	}
	return (0);
}

int	empty_line(char *line)
{
	if (!line)
		return (1);
	while (*line)
	{
		if (*line != ' ')
			return (0);
		line++;
	}
	return (1);
}
