/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkromer <jkromer@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/22 11:57:20 by jkromer           #+#    #+#             */
/*   Updated: 2021/06/19 11:52:15 by jkromer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *))
{
	t_list	*new_lst;
	t_list	*new;
	t_list	*cur;

	new_lst = ft_lstnew(f(lst->c));
	if (!new_lst)
		return (NULL);
	cur = lst->n;
	while (cur)
	{
		new = ft_lstnew(f(cur->c));
		if (!new)
		{
			ft_lstclear(&new_lst);
			return (NULL);
		}
		ft_lstadd_back(&new_lst, new);
		cur = cur->n;
	}
	return (new_lst);
}
