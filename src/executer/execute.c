/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkromer <jkromer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/21 15:55:48 by jkromer           #+#    #+#             */
/*   Updated: 2021/11/09 17:03:52 by jkromer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_list	*init_env(char **envp)
{
	t_list	*env;
	int		i;

	if (!envp || !envp[0])
		return (NULL);
	env = ft_lstnew(envp[0]);
	i = 1;
	while (envp[i])
	{
		ft_lstadd_back(&env, ft_lstnew(ft_strdup(envp[i])));
		i++;
	}
	return (env);
}

static char	**env_to_strs(t_list *env)
{
	char	**strs_env;
	int		i;
	int		len;

	len = ft_lstsize(env);
	strs_env = malloc(sizeof(char *) * (len + 1));
	i = 0;
	while (env)
	{
		strs_env[i] = env->c;
		env = env->n;
		i++;
	}
	strs_env[len] = NULL;
	return (strs_env);
}

static int	is_builtin(const char *prog)
{
	return (ft_strcmp(prog, "cd") == 0 || ft_strcmp(prog, "pwd") == 0
		|| ft_strcmp(prog, "echo") == 0 || ft_strcmp(prog, "export") == 0
		|| ft_strcmp(prog, "unset") == 0 || ft_strcmp(prog, "env") == 0
		|| ft_strcmp(prog, "exit") == 0);
}

static unsigned char	launch_builtin(
	char *const *args,
	t_list *env,
	int last_status,
	t_exec *exec)
{
	unsigned char	status;

	if (ft_strcmp(args[0], "cd") == 0)
		status = cd(args[1]);
	else if (ft_strcmp(args[0], "pwd") == 0)
		status = pwd();
	else if (ft_strcmp(args[0], "echo") == 0)
		status = echo(args);
	else if (ft_strcmp(args[0], "env") == 0)
		status = env_builtin(env);
	else if (ft_strcmp(args[0], "export") == 0)
		status = export(args, &env);
	else if (ft_strcmp(args[0], "unset") == 0)
		status = unset(args, &env);
	else
		status = exit_builtin(args, last_status);
	reset_io(exec);
	return (status);
}

int	execute(char *const *args, t_exec *exec)
{
	char	**strs_env;
	char	*full_path;

	redirect_io(exec);
	if (is_builtin(args[0]))
		return (launch_builtin(args, exec->env, exec->status, exec));
	strs_env = env_to_strs(exec->env);
	exec->pids[exec->nb_ps] = fork();
	if (exec->pids[exec->nb_ps++] == 0)
	{
		// maybe close the unused pipe end
		if (ft_starts_with(args[0], "/") || ft_starts_with(args[0], "./"))
			full_path = args[0];
		else
			full_path = search_path(args[0]);
		execve(full_path, args, strs_env);
		execute_error(args[0]);
		free(strs_env);
		exit(127);
	}
	reset_io(exec);
	free(strs_env);
	return (exec->status);
}
