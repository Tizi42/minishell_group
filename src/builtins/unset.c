/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkromer <jkromer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/20 12:36:42 by jkromer           #+#    #+#             */
/*   Updated: 2021/11/09 20:23:21 by jkromer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	match_name(const char *name, char *var)
{
	int	i;

	i = 0;
	while (name[i] && var[i] && var[i] != '=')
	{
		if (name[i] != var[i])
			return (0);
		i++;
	}
	if (name[i] == '=' && var[i] == '=')
		return (2);
	return (!name[i] && var[i] == '=');
}

int	is_in_env(const char *arg, t_list **env)
{
	t_list	*cur;

	cur = *env;
	while (cur)
	{
		if (match_name(arg, cur->c) == 2)
		{
			free(cur->c);
			cur->c = ft_strdup(arg);
			return (1);
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
		free(cur);
		return ;
	}
	while (cur && cur->n)
	{
		if (ft_strcmp(var, cur->n->c) == 0)
		{
			tmp = cur->n;
			cur->n = cur->n->n;
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
