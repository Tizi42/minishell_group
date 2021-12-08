/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkromer <jkromer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/27 15:42:47 by jkromer           #+#    #+#             */
/*   Updated: 2021/12/08 13:50:12 by jkromer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	execute_loop(t_cml *cml, t_exec *exec)
{
	int	i;

	reset_quit_handler();
	init_pids(cml, exec);
	init_pipes(exec);
	i = 0;
	while (cml[i].line)
	{
		exec->saved_stdin = dup(STDIN_FILENO);
		exec->saved_stdout = dup(STDOUT_FILENO);
		if (!set_io(cml, exec, i) || !*cml[i].lst_token->tkn->word)
			break ;
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
	close(STDIN_FILENO);
	close(STDOUT_FILENO);
	close(STDERR_FILENO);
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

	init_msh(&exec, envp);
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
			free(line);
			if (cml)
				execute_loop(cml, &exec);
		}
	}
	ft_puts("exit");
	close_pipes(&exec);
	ft_lstclear(exec.env);
	return (exec.status);
}
