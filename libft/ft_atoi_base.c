/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkromer <jkromer@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/24 19:19:02 by jkromer           #+#    #+#             */
/*   Updated: 2021/01/15 18:34:09 by jkromer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	is_valid(const char *base)
{
	int	i;
	int	j;

	if (ft_strlen(base) == 0 || ft_strlen(base) == 1)
		return (0);
	i = 0;
	while (base[i])
	{
		if (base[i] == '-' || base[i] == '+' || ft_isspace(base[i]))
			return (0);
		j = i + 1;
		while (base[j])
		{
			if (base[j] == base[i])
				return (0);
			j++;
		}
		i++;
	}
	return (1);
}

int	ft_atoi_base(const char *s, const char *base)
{
	int	i;
	int	sign;
	int	value;

	if (is_valid(base))
	{
		i = 0;
		sign = 1;
		value = 0;
		while (ft_isspace(s[i]))
			i++;
		if (s[i] == '-')
		{
			sign = -sign;
			i++;
		}
		else if (s[i] == '+')
			i++;
		while (ft_indexof(s[i], base) != -1)
			value = value * ft_strlen(base) + ft_indexof(s[i++], base);
		return (sign * value);
	}
	return (0);
}
