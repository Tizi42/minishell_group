/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tool_libft_lst.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tyuan <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/22 17:30:39 by tyuan             #+#    #+#             */
/*   Updated: 2021/10/22 17:31:53 by tyuan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_list	*ft_lstnew(void *tkn)
{
	t_list	*new;

	if (!(new = malloc(sizeof(t_list))))
		return (NULL);
	new->tkn = tkn;
	new->next = NULL;
	return (new);
}

void	ft_lstiter(t_list *lst, void (*f)(t_token *))
{
	while (lst)
	{
		(*f)(lst->tkn);
		lst = lst->next;
	}
}

void	ft_lstadd_back(t_list **alst, t_list *new)
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

t_list	*ft_lstlast(t_list *lst)
{
	t_list	*last;

	last = lst;
	while (lst)
	{
		last = lst;
		lst = lst->next;
	}
	return (last);
}

int	ft_lstsize(t_list *lst)
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
