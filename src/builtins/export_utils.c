/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkromer <jkromer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/22 16:43:45 by jkromer           #+#    #+#             */
/*   Updated: 2021/11/22 17:17:39 by jkromer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_valid(char *name)
{
	int	i;

	i = 0;
	while (name[i] && name[i] != '=')
	{
		if (name[i] == '+' && name[i + 1] == '=')
		{
			i++;
			continue ;
		}
		if (name[i] != '_' && !ft_isalnum(name[i]))
			return (0);
		i++;
	}
	return (1);
}

int	append_env(const char *arg)
{
	int	i;

	i = 0;
	while (arg[i])
	{
		if (arg[i] == '=' && i > 0 && arg[i - 1] == '+')
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strmerge_env(const char *arg, char *var)
{
	char	*join;
	char	*value;

	value = ft_strchr(arg, '=') + 1;
	join = v_malloc(sizeof(char) * (ft_strlen(var) + ft_strlen(value) + 1));
	ft_strcpy(join, var);
	ft_strcat(join, value);
	free(var);
	return (join);
}

void	increment_shlvl(t_exec *exec)
{
	t_list		*cur;
	char		*new_shlvl;
	char		*new_value;
	char *const	args[3] = {"export", "SHLVL=1", NULL};

	cur = exec->env;
	while (cur)
	{
		if (match_name("SHLVL", cur->c) == 1)
		{
			new_value = ft_itoa(ft_atoi(ft_strchr(cur->c, '=') + 1) + 1);
			new_shlvl = malloc(sizeof(char) * (ft_strlen("SHLVL=")
						+ ft_strlen(new_value) + 1));
			ft_strcpy(new_shlvl, "SHLVL=");
			ft_strcat(new_shlvl, new_value);
			free(cur->c);
			cur->c = ft_strdup(new_shlvl);
			free(new_value);
			free(new_shlvl);
			return ;
		}
		cur = cur->n;
	}
	export(args, &exec->env);
}
