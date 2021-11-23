/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkromer <jkromer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/18 16:46:40 by jkromer           #+#    #+#             */
/*   Updated: 2021/11/22 17:33:10 by jkromer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_full_path(char *arg, t_list *env)
{
	if (ft_starts_with(arg, "/") || ft_starts_with(arg, "./"))
		return (arg);
	else
		return (search_path(arg, env));
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
			if (!is_in_env(args[i], env))
				ft_lstadd_back(env, ft_lstnew(ft_strdup_env(args[i])));
		}
		i++;
	}
	return (0);
}

unsigned char	env_builtin(t_list *env)
{
	t_list	*cur;

	if (!env)
		return (0);
	cur = env;
	while (cur)
	{
		ft_puts(cur->c);
		cur = cur->n;
	}
	return (0);
}

static int	check_arg(const char *arg)
{
	int	i;

	i = 0;
	if (ft_atoul(arg) > 9223372036854775807)
		return (0);
	while (arg[i] && ft_isspace(arg[i]))
		i++;
	if (!arg[i])
		return (0);
	else if (arg[i] == '-')
		i++;
	while (arg[i])
	{
		if (!ft_isdigit(arg[i]) && arg[i] != ' ')
			return (0);
		i++;
	}
	return (1);
}

unsigned char	exit_builtin(char *const *args,	t_exec *exec, t_cml *cml)
{
	unsigned char	ret;

	close_pipes(exec);
	if (ft_puts("exit") && !args[1])
	{
		ft_lstclear(exec->env);
		clean_cml(cml);
		exit(exec->status);
	}
	else if (!check_arg(args[1]))
	{
		exit_error(args[1]);
		ft_lstclear(exec->env);
		exit(2);
	}
	else if (args[2])
	{
		exit_error(NULL);
		clean_cml(cml);
		return (1);
	}
	ret = ft_atoi(args[1]);
	clean_cml(cml);
	ft_lstclear(exec->env);
	exit(ret);
}
