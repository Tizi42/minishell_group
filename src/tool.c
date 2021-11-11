/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tool.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tyuan <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/29 17:03:44 by tyuan             #+#    #+#             */
/*   Updated: 2021/11/10 17:44:06 by jkromer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	*v_malloc(size_t size)
{
	void	*ret;

	ret = malloc(size);
	if (!ret)
		exit (0);
	return (ret);
}

void	cleanup(char **paths, char *new_prog)
{
	free(new_prog);
	free_split(paths);
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
			return(ft_strdup(ft_strchr(cur->c, '=') + 1));
		cur = cur->n;
	}
	return (ft_strdup(NULL));
}
