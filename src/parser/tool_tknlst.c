/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tool_tknlst.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tyuan <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/22 17:30:39 by tyuan             #+#    #+#             */
/*   Updated: 2021/10/30 13:59:26 by tyuan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_tknlst	*tknlstnew(void *tkn)
{
	t_tknlst	*new;

	new = v_malloc(sizeof(t_tknlst));
	new->tkn = tkn;
	new->next = NULL;
	return (new);
}

void	tknlstiter(t_tknlst *lst, void *optional, void (*f)(t_token *, void *op))
{
	while (lst)
	{
		(*f)(lst->tkn, optional);
		lst = lst->next;
	}
}

void	tknlstadd_back(t_tknlst **alst, t_tknlst *new)
{
	if (*alst == NULL)
	{
		*alst = new;
		return ;
	}
	while (alst && (*alst)->next)
		alst = &((*alst)->next);
	(*alst)->next = new;
}

t_tknlst	*tknlstlast(t_tknlst *lst)
{
	t_tknlst	*last;

	last = lst;
	while (lst)
	{
		last = lst;
		lst = lst->next;
	}
	return (last);
}

int	tknlstsize(t_tknlst *lst)
{
	int	s;

	s = 0;
	while (lst)
	{
		s++;
		lst = lst->next;
	}
	return (s);
}
