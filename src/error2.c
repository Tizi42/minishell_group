/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkromer <jkromer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/08 13:26:37 by jkromer           #+#    #+#             */
/*   Updated: 2021/11/08 17:13:30 by jkromer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	open_error(const char *file)
{
	perror(file);
	return (0);
}

void	syntax_error(const char *arg)
{
	write(2, "Syntax error: ", 14);
	write(2, arg, ft_strlen(arg));
	write(2, "\n", 1);
}

void	unix_error(char *msg)
{
	perror(msg);
	exit (-1);
}
