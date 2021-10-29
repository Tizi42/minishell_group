/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkromer <jkromer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/20 12:36:42 by jkromer           #+#    #+#             */
/*   Updated: 2021/10/23 20:01:08 by jkromer          ###   ########.fr       */
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
	return (!name[i] && var[i] == '=');
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
			if (match_name(args[i], cur->c))
			{
				tmp = cur->n;
				delete_var(env, cur->c);
				cur = tmp;
			}
			i++;
		}
		cur = cur->n;
	}
	return (0);
}
