/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   io.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkromer <jkromer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/03 12:15:10 by jkromer           #+#    #+#             */
/*   Updated: 2021/11/07 12:24:07 by jkromer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	set_io(t_cml *cml, t_exec *exec, int i)
{
	int	is_pipe;

	exec->in = STDIN_FILENO;
	exec->out = STDOUT_FILENO;
	is_pipe = (cml[i + 1].line != NULL);
	if (is_pipe)
	{
		pipe(exec->pipe_fds[exec->nb_pipe]);
		exec->out = exec->pipe_fds[exec->nb_pipe][1];
	}
	if (i > 0)
		exec->in = exec->pipe_fds[abs(exec->nb_pipe - 1)][0];
	if (is_pipe)
	{
		exec->nb_pipe++;
		if (exec->nb_pipe > 1)
			exec->nb_pipe = 0;
	}
}

void	redirect_io(t_exec *exec)
{
	if (exec->in != STDIN_FILENO)
	{
		dup2(exec->in, STDIN_FILENO);
		close(exec->in);
	}
	if (exec->out != STDOUT_FILENO)
	{
		dup2(exec->out, STDOUT_FILENO);
		close(exec->out);
	}
}

void	reset_io(t_exec *exec)
{
	dup2(exec->saved_stdin, STDIN_FILENO);
	dup2(exec->saved_stdout, STDOUT_FILENO);
	close(exec->saved_stdin);
	close(exec->saved_stdout);
}
