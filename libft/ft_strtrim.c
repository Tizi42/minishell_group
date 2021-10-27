/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkromer <jkromer@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/19 11:25:27 by jkromer           #+#    #+#             */
/*   Updated: 2021/01/15 19:02:07 by jkromer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *str, char const *set)
{
	int		i;
	size_t	start;
	size_t	len;
	size_t	str_len;

	str_len = ft_strlen(str);
	if (!str || !str_len)
		return (ft_strdup(""));
	i = 0;
	while (str[i] && ft_contains(set, str[i]))
		i++;
	start = i;
	i = str_len - 1;
	while (i >= 0 && ft_contains(set, str[i]))
		i--;
	len = (i - start) + 1;
	if (len > str_len)
		return (ft_strdup(""));
	return (ft_substr(str, start, len));
}
