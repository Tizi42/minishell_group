/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkromer <jkromer@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/19 14:47:45 by jkromer           #+#    #+#             */
/*   Updated: 2021/01/15 18:39:16 by jkromer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	count_chars(long int n)
{
	size_t		size;
	long int	nb;

	nb = n;
	size = 1;
	while (nb)
	{
		size++;
		nb /= 10;
	}
	if (n < 0)
		size++;
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
	if (n == 0)
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
