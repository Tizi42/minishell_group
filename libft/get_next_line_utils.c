/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_n_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkromer <jkromer@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/13 21:12:58 by jkromer           #+#    #+#             */
/*   Updated: 2021/06/22 12:30:46 by jkromer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	fill_buffer(int fd, char *buffer, int *n)
{
	*n = read(fd, buffer, BUFFER_SIZE);
	if (*n == -1)
		return (-1);
	buffer[*n] = 0;
	return (0);
}

void	clear_gnl(int fd)
{
	close(fd);
	get_n_line(fd, NULL);
}
