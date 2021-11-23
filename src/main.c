/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkromer <jkromer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/27 15:42:47 by jkromer           #+#    #+#             */
/*   Updated: 2021/11/18 17:52:53 by jkromer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	execute_loop(t_cml *cml, t_exec *exec)
{
	int	i;

	reset_quit_handler();
	exec->nb_ps = 0;
	exec->nb_pipe = 0;
	init_pids(cml, exec);
	init_pipes(exec);
	i = 0;
	while (cml[i].line)
	{
		exec->saved_stdin = dup(STDIN_FILENO);
		exec->saved_stdout = dup(STDOUT_FILENO);
		set_io(cml, exec, i);
		exec->status = execute(cml[i].argv, exec, cml);
		i++;
	}
	wait_processes(exec);
	g_sig.pid = -1;
	init_signals();
	free(exec->pids);
	clean_cml(cml);
}

void	ignore_sig(void)
{
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, SIG_IGN);
}

void	close_std_fds(void)
{
	close(0);
	close(1);
	close(2);
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

	exec = init_msh(envp);
	increment_shlvl(&exec);
	init_signals();
	while (isatty(STDIN_FILENO))
	{
		line = readline("msh$ ");
		if (!line)
			break ;
		if (*line && !empty_line(line))
		{
			add_history(line);
			cml = parse(line, exec);
			if (cml)
				execute_loop(cml, &exec);
		}
		free(line);
	}
	ft_puts("exit");
	close_pipes(&exec);
	ft_lstclear(exec.env);
	return (exec.status);
}
