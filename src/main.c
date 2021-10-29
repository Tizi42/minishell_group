/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkromer <jkromer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/27 15:42:47 by jkromer           #+#    #+#             */
/*   Updated: 2021/10/27 19:55:54 by jkromer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <readline/readline.h>
#include "parse.h"
#include "execute.h"
#include "builtins.h"

int	main(
	int ac __attribute__((unused)),
	char **av __attribute__((unused)),
	char **envp)
{
	char	*line;
	t_cml	*cml;
	t_list	*env;
	int		i;
	int		last_status;

	last_status = 0;
	env = init_env(envp);
	while(isatty(STDIN_FILENO))
	{
		line = readline("$ ");
		if (!line)
			exit_builtin(NULL, last_status);
		cml = parse(line);  // parse(line, env, last_status);
		i = 0;
		while (cml[i].line)
		{
			last_status = execute(cml[i].argv, env, last_status);
			i++;
		}
	}
	ft_lstclear(&env);
	free(line);
	free(cml);
}
