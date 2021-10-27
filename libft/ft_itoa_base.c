/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkromer <jkromer@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/19 14:47:45 by jkromer           #+#    #+#             */
/*   Updated: 2021/01/15 18:40:52 by jkromer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	count_chars(long int n, size_t base_len)
{
	size_t		size;
	long int	nb;

	nb = n;
	size = 1;
	while (nb)
	{
		size++;
		nb /= base_len;
	}
	if (n < 0)
		size++;
	return (size);
}

static char	*init_vars(long int *nb, int n, size_t *base_len, const char *base)
{
	*nb = n;
	*base_len = ft_strlen(base);
	return (malloc(sizeof(char) * (count_chars(*nb, *base_len) + 1)));
}

char	*ft_itoa_base(int n, const char *base)
{
	char		*nbr;
	size_t		size;
	size_t		base_len;
	int			i;
	long int	nb;

	nbr = init_vars(&nb, n, &base_len, base);
	size = count_chars(nb, base_len);
	if (!nbr)
		return (NULL);
	if (n == 0)
		nbr[0] = base[0];
	else if (nb < 0)
	{
		nb = -nb;
		nbr[0] = '-';
	}
	i = size - 1;
	while (nb)
	{
		nbr[i--] = base[nb % base_len];
		nb /= base_len;
	}
	nbr[size] = 0;
	return (nbr);
}
