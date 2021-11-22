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
