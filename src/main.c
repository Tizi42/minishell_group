/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkromer <jkromer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/27 15:42:47 by jkromer           #+#    #+#             */
/*   Updated: 2021/11/03 09:06:48 by jkromer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(
	int ac __attribute__((unused)),
	char **av __attribute__((unused)),
	char **envp
)
{
	char	*line;
	t_cml	*cml;
	t_list	*env;
	int		i;
	int		last_status;

	last_status = 0;
	env = init_env(envp);
	while (isatty(STDIN_FILENO))
	{
		line = readline("msh$ ");
		if (!line)
			exit_builtin(NULL, last_status);
		cml = parse(line);  // parse(line, env, last_status);
		i = 0;
		while (cml[i].line)
		{
			last_status = execute(cml[i].argv, env, last_status);
			i++;
		}
		free(line);
		free(cml);
	}
	ft_lstclear(&env);
}
