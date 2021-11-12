/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkromer <jkromer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/27 15:42:47 by jkromer           #+#    #+#             */
/*   Updated: 2021/11/12 15:06:28 by jkromer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

struct s_sig	g_sig;

static void	wait_processes(t_exec *exec)
{
	int	i;

	i = 0;
	while (i < exec->nb_ps)
	{
		waitpid(exec->pids[i], &exec->status, 0);
		if (WIFSIGNALED(exec->status))
			exec->status = WTERMSIG(exec->status) + 128;
		if (WIFEXITED(exec->status))
			exec->status = WEXITSTATUS(exec->status);
		i++;
	}
}

static void	init_pids(t_cml *cml, t_exec *exec)
{
	int	i;

	i = 0;
	while (cml[i].line)
		i++;
	exec->pids = malloc(sizeof(pid_t) * i);
}

static void	execute_loop(t_cml *cml, t_exec *exec)
{
	int	i;

	reset_quit_handler();
	exec->nb_ps = 0;
	exec->nb_pipe = 0;
	init_pids(cml, exec);
	init_pipes(exec);
	if (!exec->pids)
		return ;
	i = 0;
	while (cml[i].line)
	{
		exec->saved_stdin = dup(STDIN_FILENO);
		exec->saved_stdout = dup(STDOUT_FILENO);
		if (!set_io(cml, exec, i) || !cml[i].lst_token->tkn->word)
			return ;
		exec->status = execute(cml[i].argv, exec);
		i++;
	}
	wait_processes(exec);
	g_sig.pid = 0;
	init_signals();
	free(exec->pids);
	clean_cml(cml);
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
	g_sig.pid = 0;
	g_sig.status = &exec.status;
	init_signals();
	while (isatty(STDIN_FILENO))
	{
		line = readline("msh$ ");
		if (!line)
			break ;
		if (*line)
			add_history(line);
		cml = parse(line, exec);
		if (cml)
			execute_loop(cml, &exec);
		free(line);
	}
	ft_puts("exit");
	ft_lstclear(exec.env);
	return (exec.status);
}
