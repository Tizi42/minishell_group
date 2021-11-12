/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoul.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkromer <jkromer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/12 16:50:52 by jkromer           #+#    #+#             */
/*   Updated: 2021/11/12 16:57:14 by jkromer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

unsigned long long	ft_atoul(const char *s)
{
	unsigned long long	value;
	int					i;

	if (!s)
		return (0);
	value = 0;
	i = 0;
	while (ft_isspace(s[i]))
		i++;
	if (s[i] == '+')
		i++;
	while (ft_isdigit(s[i]))
	{
		value = value * 10 + (s[i] - '0');
		i++;
	}
	return (value);
}
