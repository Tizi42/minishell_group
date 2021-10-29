/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_contains.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkromer <jkromer@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/13 18:08:12 by jkromer           #+#    #+#             */
/*   Updated: 2021/01/15 18:35:30 by jkromer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_contains(const char *str, char c)
{
	while (*str)
		if (*str++ == c)
			return (1);
	return (0);
}
