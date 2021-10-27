/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkromer <jkromer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/21 15:55:48 by jkromer           #+#    #+#             */
/*   Updated: 2021/10/27 17:46:21 by jkromer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/wait.h>
#include "error.h"
#include "builtins.h"
#include "execute.h"

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
		ft_lstadd_back(&env, ft_lstnew(envp[i]));
		i++;
	}
	return (env);
}

static char	**get_strs(t_list *env)
{
	char	**str_env;
	int		i;
	int		len;

	len = ft_lstsize(env);
	str_env = malloc(sizeof(char *) * (len + 1));
	i = 0;
	while (env)
	{
		str_env[i] = env->c;
		env = env->n;
		i++;
	}
	str_env[len] = NULL;
	return (str_env);
}

static int	is_builtin(const char *prog)
{
	return (ft_strcmp(prog, "cd") == 0 || ft_strcmp(prog, "pwd") == 0
		|| ft_strcmp(prog, "echo") == 0 || ft_strcmp(prog, "export") == 0
		|| ft_strcmp(prog, "unset") == 0 || ft_strcmp(prog, "env") == 0
		|| ft_strcmp(prog, "exit") == 0);
}

static unsigned char	launch_builtin(char *const *args, t_list *env)
{
	if (ft_strcmp(args[0], "cd") == 0)
		return (cd(args[1]));
	else if (ft_strcmp(args[0], "pwd") == 0)
		return (pwd());
	else if (ft_strcmp(args[0], "echo") == 0)
		return (echo(args));
	else if (ft_strcmp(args[0], "env") == 0)
		return (env_builtin(env));
	else if (ft_strcmp(args[0], "export") == 0)
		return (export(args, &env));
	else if (ft_strcmp(args[0], "unset") == 0)
		return (unset(args, &env));
	else
		return (exit_builtin(args, 9)); // GET LAST_STATUS
}

int	execute(char *const *args, t_list *env)
{
	pid_t	child;
	char	**str_env;
	char	*full_path;
	int		status;

	if (is_builtin(args[0]))
		return (launch_builtin(args, env));
	str_env = get_strs(env);
	status = 0;
	child = fork();
	if (child == 0)
	{
		full_path = search_path(args[0]);
		execve(full_path, args, str_env);
		execute_error(args[0]);
		free(str_env);
		exit(127);
	}
	waitpid(child, &status, 0);
	free(str_env);
	return (status);
}
