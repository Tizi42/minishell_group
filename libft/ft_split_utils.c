/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkromer <jkromer@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/17 17:41:16 by jkromer           #+#    #+#             */
/*   Updated: 2021/01/19 23:21:46 by jkromer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	is_sep(char c, const char *sep)
{
	int	i;

	i = 0;
	while (sep[i])
		if (sep[i++] == c)
			return (1);
	return (0);
}

void	free_split(char **split)
{
	int	i;

	i = -1;
	while (split[++i])
		free(split[i]);
	free(split);
}

int	count_elems(char **split)
{
	int	i;

	i = 0;
	while (split[i])
		i++;
	return (i);
}
