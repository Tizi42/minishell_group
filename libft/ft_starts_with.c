/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_starts_with.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkromer <jkromer@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/13 14:41:18 by jkromer           #+#    #+#             */
/*   Updated: 2021/01/15 18:57:01 by jkromer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_starts_with(const char *str, const char *pattern)
{
	return (!ft_strncmp(str, pattern, ft_strlen(pattern)));
}
