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

int		if_unquoted_space(t_list *lst)
{
	while (lst)
	{
		if (lst->content->type == UNQUOTED_SPACE)
			return (1);
		lst = lst->next;
	}
	return (0);
}
