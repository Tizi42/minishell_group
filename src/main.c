/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkromer <jkromer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/27 15:42:47 by jkromer           #+#    #+#             */
/*   Updated: 2021/11/11 12:15:42 by jkromer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

struct s_sig	g_sig;

static void	execute_loop(t_cml *cml, t_exec *exec)
{
	int	i;
	int	j;

	reset_quit_handler();
	exec->nb_ps = 0;
	exec->nb_pipe = 0;
	i = 0;
	while (cml[i].line)
	{
		exec->saved_stdin = dup(STDIN_FILENO);
		exec->saved_stdout = dup(STDOUT_FILENO);
		if (!set_io(cml, exec, i))
			return ;
		if (!cml[i].lst_token->tkn->word)
			return ;
		exec->status = execute(cml[i].argv, exec);
		j = 0;
		while (j < exec->nb_ps)
			waitpid(exec->pids[j++], &exec->status, 0);
		i++;
	}
	g_sig.pid = 0;
	init_signals();
	free(cml);
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
		if (cml && cml->argv)
			execute_loop(cml, &exec);
		free(line);
	}
	ft_lstclear(exec.env);
	exit_builtin(NULL, exec.status);
}
