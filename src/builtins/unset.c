/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkromer <jkromer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/20 12:36:42 by jkromer           #+#    #+#             */
/*   Updated: 2021/12/08 14:18:29 by jkromer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	match_name(const char *name, char *var)
{
	int	i;

	i = 0;
	while (name[i] && var[i] && var[i] != '=')
	{
		if (name[i] != var[i])
			return (0);
		i++;
	}
	if ((name[i] == '=' || name[i] == '+') && var[i] == '=')
		return (2);
	return (!name[i] && var[i] == '=');
}

char	*ft_strdup_env(const char *arg)
{
	char	*dup;
	int		i;
	int		j;
	int		ignore;

	dup = v_malloc(sizeof(char) * (ft_strlen(arg) + 1));
	i = 0;
	j = 0;
	ignore = 0;
	while (arg[i])
	{
		if (arg[i] == '+' && arg[i + 1] == '=' && !ignore)
			ignore = 1;
		else
			dup[j++] = arg[i];
		i++;
	}
	dup[i] = 0;
	return (dup);
}

int	is_in_env(const char *arg, t_list **env)
{
	t_list	*cur;

	cur = *env;
	while (cur)
	{
		if (match_name(arg, cur->c) == 2)
		{
			if (!append_env(arg))
			{
				free(cur->c);
				cur->c = ft_strdup_env(arg);
				return (1);
			}
			else
			{
				cur->c = ft_strmerge_env(arg, cur->c);
				return (1);
			}
		}
		cur = cur->n;
	}
	return (0);
}

static void	delete_var(t_list **env, const char *var)
{
	t_list	*cur;
	t_list	*tmp;

	cur = *env;
	if (ft_strcmp(var, cur->c) == 0)
	{
		*env = cur->n;
		free(cur->c);
		free(cur);
		return ;
	}
	while (cur && cur->n)
	{
		if (ft_strcmp(var, cur->n->c) == 0)
		{
			tmp = cur->n;
			cur->n = cur->n->n;
			free(tmp->c);
			free(tmp);
			break ;
		}
		cur = cur->n;
	}
}

unsigned char	unset(char *const *args, t_list **env)
{
	t_list	*cur;
	t_list	*tmp;
	int		i;

	cur = *env;
	while (cur)
	{
		i = 1;
		while (args[i])
		{
			if (match_name(args[i], cur->c) == 1)
			{
				tmp = cur->n;
				delete_var(env, cur->c);
				if (!tmp)
					return (0);
				cur = tmp;
			}
			i++;
		}
		cur = cur->n;
	}
	return (0);
}
