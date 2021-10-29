/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_indexof.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkromer <jkromer@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/24 19:12:54 by jkromer           #+#    #+#             */
/*   Updated: 2021/01/15 18:36:12 by jkromer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_indexof(char c, const char *s)
{
	int	index;

	index = 0;
	if (!*s)
		return (-1);
	while (s[index])
	{
		if (s[index] == c)
			return (index);
		index++;
	}
	return (-1);
}
