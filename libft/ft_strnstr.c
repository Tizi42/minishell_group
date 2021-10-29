/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkromer <jkromer@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/18 14:16:50 by jkromer           #+#    #+#             */
/*   Updated: 2021/01/15 19:00:53 by jkromer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	j;

	if (!little[0])
		return ((char *)big);
	i = 0;
	while (i < len && big[i])
	{
		j = 0;
		while (little[j] && i + j < len && little[j] == big[i + j])
			j++;
		if (little[j] == 0)
			return ((char *)big + i);
		i++;
	}
	return (NULL);
}
