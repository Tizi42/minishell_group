/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_search.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkromer <jkromer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/27 15:50:11 by jkromer           #+#    #+#             */
/*   Updated: 2021/10/27 16:54:53 by jkromer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	cleanup(char **paths, char *new_prog)
{
	free(new_prog);
	free_split(paths);
}

char	*search_path(const char *prog)
{
	char	**paths;
	char	*env_path;
	char	*full_path;
	char	*new_prog;
	int		i;

	env_path = getenv("PATH");
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
