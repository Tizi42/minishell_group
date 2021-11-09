/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkromer <jkromer@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/21 20:22:22 by jkromer           #+#    #+#             */
/*   Updated: 2021/11/09 17:04:29 by jkromer          ###   ########.fr       */
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
		free(cur->c);
		free(cur);
	}
	*lst = NULL;
}
