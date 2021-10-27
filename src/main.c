/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkromer <jkromer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/27 15:42:47 by jkromer           #+#    #+#             */
/*   Updated: 2021/10/27 16:58:43 by jkromer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <readline/readline.h>
#include "parse.h"
#include "execute.h"

int	main(int ac, char **av, char **envp)
{
	char	*line;
	t_cml	*cml;
	t_list	*env;
	int		i;

	(void)ac;
	(void)av;
	env = init_env(envp);
	while (1)
	{
		line = readline("$ ");
		cml = parse(line);
		i = 0;
		while (cml[i].line)
		{
			execute(cml[i].argv, env);
			i++;
		}
	}
	ft_lstclear(&env);
	free(line);
	free(cml);
}
