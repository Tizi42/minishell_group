/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkromer <jkromer@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/19 14:47:45 by jkromer           #+#    #+#             */
/*   Updated: 2021/11/11 13:05:27 by jkromer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	count_chars(long int n)
{
	size_t		size;

	size = 0;
	if (n == 0)
		return (1);
	else if (n < 0)
	{
		size++;
		n = -n;
	}
	while (n)
	{
		size++;
		n /= 10;
	}
	return (size);
}

char	*ft_itoa(int n)
{
	char		*nbr;
	size_t		size;
	int			i;
	long int	nb;

	nb = n;
	size = count_chars(nb);
	nbr = malloc(sizeof(char) * (size + 1));
	if (!nbr)
		return (NULL);
	if (nb == 0)
		nbr[0] = '0';
	i = size - 1;
	if (nb < 0)
	{
		nb = -nb;
		nbr[0] = '-';
	}
	while (nb)
	{
		nbr[i--] = (nb % 10) + '0';
		nb /= 10;
	}
	nbr[size] = 0;
	return (nbr);
}
