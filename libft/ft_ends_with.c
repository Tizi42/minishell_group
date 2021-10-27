/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ends_with.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkromer <jkromer@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/13 14:42:39 by jkromer           #+#    #+#             */
/*   Updated: 2021/01/15 18:35:49 by jkromer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_ends_with(const char *str, const char *pattern)
{
	int	offset;

	offset = ft_strlen(str) - ft_strlen(pattern);
	return (!ft_strncmp(str + offset, pattern, ft_strlen(pattern)));
}
