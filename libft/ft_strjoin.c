/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkromer <jkromer@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/19 10:33:23 by jkromer           #+#    #+#             */
/*   Updated: 2021/01/15 18:58:54 by jkromer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	total_len(size_t size, const char **strs, const char *sep)
{
	size_t	total;
	size_t	i;

	total = 0;
	i = 0;
	while (i < size)
	{
		total += ft_strlen(strs[i]);
		if (i != size - 1)
			total += ft_strlen(sep);
		i++;
	}
	return (total);
}

char	*ft_strjoin(size_t size, const char **strs, const char *sep)
{
	char	*join;
	size_t	i;

	join = malloc(sizeof(char) * (total_len(size, strs, sep) + 1));
	if (!join)
		return (NULL);
	join[0] = 0;
	i = 0;
	while (i < size)
	{
		ft_strcat(join, strs[i]);
		if (i != size - 1)
			ft_strcat(join, sep);
		i++;
	}
	return (join);
}
