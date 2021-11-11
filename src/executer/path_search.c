/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_search.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkromer <jkromer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/27 15:50:11 by jkromer           #+#    #+#             */
/*   Updated: 2021/11/11 11:45:34 by jkromer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*ft_getenv(t_list *env, const char *var)
{
	while (env)
	{
		if (match_name(var, env->c) == 1)
			return (env->c);
		env = env->n;
	}
	return (NULL);
}

char	*search_path(const char *prog, t_list *env)
{
	char	**paths;
	char	*env_path;
	char	*full_path;
	char	*new_prog;
	int		i;

	env_path = ft_getenv(env, "PATH");
	if (!env_path)
		return (NULL);
	paths = ft_split(env_path, ":");
	new_prog = ft_strmerge("/", prog);
	i = -1;
	while (paths[++i])
	{
		full_path = ft_strmerge(paths[i], new_prog);
		if (access(full_path, X_OK) == 0)
		{
			cleanup(paths, new_prog);
			return (full_path);
		}
		free(full_path);
	}
	cleanup(paths, new_prog);
	return (NULL);
}
