/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkromer <jkromer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/27 15:50:11 by jkromer           #+#    #+#             */
/*   Updated: 2021/11/18 17:45:34 by jkromer          ###   ########.fr       */
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

int	has_pipe(t_exec *exec)
{
	int	i;
	int	j;

	i = 0;
	while (i <= 1)
	{
		j = 0;
		while (j <= 1)
		{
			if (exec->pipe_fds[i][j] != -1)
				return (1);
			j++;
		}
		i++;
	}
	return (0);
}

unsigned char	exec_builtins(char *const *args, t_exec *exec, t_cml *cml)
{
	unsigned char	status;

	status = 0;
	if (ft_strcmp(args[0], "cd") == 0)
		status = cd(args[1]);
	else if (ft_strcmp(args[0], "pwd") == 0)
		status = pwd();
	else if (ft_strcmp(args[0], "echo") == 0)
		status = echo(args);
	else if (ft_strcmp(args[0], "env") == 0)
		status = env_builtin(exec->env);
	else if (ft_strcmp(args[0], "export") == 0)
		status = export(args, &exec->env);
	else if (ft_strcmp(args[0], "unset") == 0)
		status = unset(args, &exec->env);
	else
		status = exit_builtin(args, exec, cml);
	return (status);
}
