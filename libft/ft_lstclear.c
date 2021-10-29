/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkromer <jkromer@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/21 20:22:22 by jkromer           #+#    #+#             */
/*   Updated: 2021/06/19 17:14:17 by jkromer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst)
{
	t_list	*cur;
	t_list	*n;

	n = *lst;
	while (n)
	{
		cur = n;
		n = cur->n;
		free(cur);
	}
	*lst = NULL;
}
