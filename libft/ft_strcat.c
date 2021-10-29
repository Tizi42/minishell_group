/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcat.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkromer <jkromer@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/19 10:55:09 by jkromer           #+#    #+#             */
/*   Updated: 2021/01/15 18:57:15 by jkromer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strcat(char *dst, const char *src)
{
	int		i;
	size_t	dst_len;

	i = -1;
	dst_len = ft_strlen(dst);
	while (src[++i])
		dst[dst_len + i] = src[i];
	dst[dst_len + i] = 0;
	return (dst);
}
