/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkromer <jkromer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/18 10:29:48 by jkromer           #+#    #+#             */
/*   Updated: 2021/10/27 12:05:04 by jkromer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include "libft.h"
#include "error.h"

#define MAX_DIR_SIZE 4096

unsigned char	cd(const char *path)
{
	int	r;

	if (!path)
		r = chdir(getenv("HOME"));
	else
		r = chdir(path);
	if (r == -1)
	{
		print_error("cd", path);
		return (1);
	}
	return (0);
}

unsigned char	pwd(void)
{
	char	dir_name[MAX_DIR_SIZE];

	if (!getcwd(dir_name, MAX_DIR_SIZE))
	{
		print_error("pwd", NULL);
		return (1);
	}
	ft_puts(dir_name);
	return (0);
}

static int	check_option(const char *opt)
{
	int	i;

	if (opt[0] != '-')
		return (0);
	i = 1;
	while (opt[i])
	{
		if (opt[i] != 'n')
			return (0);
		i++;
	}
	return (1);
}

unsigned char	echo(char *const *args)
{
	int	i;
	int	no_nl;

	if (!args[1])
		no_nl = 0;
	else if (check_option(args[1]))
		no_nl = 1;
	else
		no_nl = 0;
	i = no_nl + 1;
	while (args[i])
	{
		ft_putstr(args[i]);
		if (args[i + 1])
			write(1, " ", 1);
		i++;
	}
	if (!no_nl)
		write(1, "\n", 1);
	return (0);
}
