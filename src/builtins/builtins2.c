/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkromer <jkromer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/18 16:46:40 by jkromer           #+#    #+#             */
/*   Updated: 2021/11/11 14:08:38 by jkromer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_valid(char *name)
{
	int	i;

	i = 0;
	while (name[i] && name[i] != '=')
	{
		if (name[i] != '_' && !ft_isalnum(name[i]))
			return (0);
		i++;
	}
	return (1);
}

unsigned char	export(char *const *args, t_list **env)
{
	int	i;

	i = 1;
	if (!args[1])
	{
		env_builtin(*env);
		return (0);
	}
	while (args[i])
	{
		if (!is_valid(args[i]))
		{
			export_error(args[i]);
			return (1);
		}
		if (ft_contains(args[i], '='))
		{
			if (is_in_env(args[i], env))
				;
			else
				ft_lstadd_back(env, ft_lstnew(args[i]));
		}
		i++;
	}
	return (0);
}

unsigned char	env_builtin(const t_list *env)
{
	if (!env)
		return (0);
	while (env)
	{
		ft_puts(env->c);
		env = env->n;
	}
	return (0);
}

static int	check_arg(const char *arg)
{
	int	i;

	i = 0;
	while (arg[i] && ft_isspace(arg[i]))
		i++;
	if (!arg[i])
		return (0);
	else if (arg[i] == '-')
		i++;
	while (arg[i])
	{
		if (!ft_isdigit(arg[i]))
			return (0);
		i++;
	}
	return (1);
}

unsigned char	exit_builtin(char *const *args,	t_exec *exec)
{
	ft_puts("exit");
	if (!args[1])
	{
		ft_lstclear(exec->env);
		exit(exec->status);
	}
	else if (args[2])
	{
		exit_error(NULL);
		ft_lstclear(exec->env);
		return (1);
	}
	else if (!check_arg(args[1]))
	{
		exit_error(args[1]);
		ft_lstclear(exec->env);
		exit(2);
	}
	ft_lstclear(exec->env);
	exit((unsigned char)ft_atoi(args[1]));
}
