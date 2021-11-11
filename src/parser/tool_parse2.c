/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tool_parse2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tyuan <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/22 17:30:55 by tyuan             #+#    #+#             */
/*   Updated: 2021/10/22 17:31:30 by tyuan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	if_unquoted_space(t_tknlst *lst)
{
	while (lst)
	{
		if (lst->tkn->type == UNQUOTED_SPACE)
			return (1);
		lst = lst->next;
	}
	return (0);
}

char	*quoted_bit_reset(char *line, char c, int *type)
{
	char	*quo;
	int		n;

	quo = v_malloc(sizeof(char) * (ft_strlen(line) + 1));
	n = 0;
	while (line[n])
	{
		if (line[n] == ' ' && c == NQ)
			*type = UNQUOTED_SPACE;
		quo[n++] = c;
	}
	quo[n] = '\0';
	return (quo);
}

void	init_cml(t_cml *cmls)
{
	cmls->lst_redi = NULL;
	cmls->lst_token = NULL;
	cmls->line = NULL;
	cmls->argv = NULL;
}
