/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkromer <jkromer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/27 15:42:47 by jkromer           #+#    #+#             */
/*   Updated: 2021/11/03 16:12:40 by jkromer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	execute_loop(t_cml *cml, t_exec exec)
{
	int	i;

	i = 0;
	while (cml[i].line)
	{
		set_io(cml, &exec, i);
		exec.status = execute(cml[i].argv, exec);
		i++;
	}
}

int	main(
	int ac __attribute__((unused)),
	char **av __attribute__((unused)),
	char **envp
)
{
	char	*line;
	t_cml	*cml;
	t_exec	exec;

	exec.status = 0;
	exec.env = init_env(envp);
	while (isatty(STDIN_FILENO))
	{
		line = readline("msh$ ");
		if (!line)
			exit_builtin(NULL, exec.status);
		cml = parse(line);  // parse(line, env, exec.status);
		execute_loop(cml, exec);
		free(line);
		free(cml);
	}
	ft_lstclear(&exec.env);
}
