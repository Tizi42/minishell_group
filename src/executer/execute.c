/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkromer <jkromer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/21 15:55:48 by jkromer           #+#    #+#             */
/*   Updated: 2021/11/22 17:39:57 by jkromer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_list	*init_env(char **envp)
{
	t_list	*env;
	int		i;

	if (!envp || !envp[0])
		return (NULL);
	env = ft_lstnew(ft_strdup(envp[0]));
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

static unsigned char	launch_builtin(char *const *args, t_exec *exec,
	t_cml *cml)
{
	unsigned char	status;

	status = 0;
	if (has_pipe(exec))
	{
		exec->pids[exec->nb_ps] = fork();
		g_sig.pid = exec->pids[exec->nb_ps];
		if (exec->pids[exec->nb_ps++] == 0)
		{
			close_pipes(exec);
			status = exec_builtins(args, exec, cml);
			exit(status);
		}
	}
	else
		status = exec_builtins(args, exec, cml);
	reset_io(exec);
	return (status);
}

int	execute(char *const *args, t_exec *exec, t_cml *cml)
{
	char	**strs_env;
	char	*full_path;

	redirect_io(exec);
	if (is_builtin(args[0]))
		return (launch_builtin(args, exec, cml));
	strs_env = env_to_strs(exec->env);
	exec->pids[exec->nb_ps] = fork();
	g_sig.pid = exec->pids[exec->nb_ps];
	if (exec->pids[exec->nb_ps++] == 0)
	{
		close_pipes(exec);
		if (ft_starts_with(args[0], "/") || ft_starts_with(args[0], "./"))
			full_path = args[0];
		else
			full_path = search_path(args[0], exec->env);
		execve(full_path, args, strs_env);
		execute_error(args[0]);
		free(strs_env);
		exit(127);
	}
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, SIG_IGN);
	reset_io(exec);
	free(strs_env);
	return (exec->status);
}
