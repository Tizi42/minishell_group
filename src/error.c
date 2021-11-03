/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkromer <jkromer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/18 10:46:00 by jkromer           #+#    #+#             */
/*   Updated: 2021/10/23 20:04:01 by jkromer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <errno.h>
#include <string.h>
#include "libft.h"

void	print_error(const char *prog, const char *arg)
{
	char	*error;

	error = strerror(errno);
	write(2, prog, ft_strlen(prog));
	write(2, ": ", 2);
	if (arg)
	{
		write(2, arg, ft_strlen(arg));
		write(2, ": ", 2);
	}
	write(2, error, ft_strlen(error));
	write(2, "\n", 1);
}

void	export_error(const char *arg)
{
	write(2, "export: `", 9);
	write(2, arg, ft_strlen(arg));
	write(2, "': not a valid identifier\n", 26);
}

void	exit_error(const char *arg)
{
	write(2, "exit: ", 6);
	if (arg)
	{
		write(2, arg, ft_strlen(arg));
		write(2, ": numeric argument required\n", 28);
	}
	else
		write(2, "too many arguments\n", 19);
}

void	execute_error(const char *arg)
{
	write(2, arg, ft_strlen(arg));
	write(2, ": command not found\n", 20);
}
