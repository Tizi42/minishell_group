/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkromer <jkromer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/27 15:42:47 by jkromer           #+#    #+#             */
/*   Updated: 2021/11/09 20:07:37 by jkromer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	execute_loop(t_cml *cml, t_exec *exec)
{
	int	i;
	int	j;

	exec->nb_ps = 0;
	exec->nb_pipe = 0;
	i = 0;
	while (cml[i].line)
	{
		exec->saved_stdin = dup(STDIN_FILENO);
		exec->saved_stdout = dup(STDOUT_FILENO);
		if (!set_io(cml, exec, i))
			return ;
		exec->status = execute(cml[i].argv, exec);
		j = 0;
		while (j < exec->nb_ps)
			waitpid(exec->pids[j++], &exec->status, 0);
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
		if (*line)
			add_history(line);
		cml = parse(line, exec);
		if (cml)
			execute_loop(cml, &exec); //free cml at the end of execute_loop()
		free(line);
	}
	free(cml);
	ft_lstclear(&exec.env);
}
