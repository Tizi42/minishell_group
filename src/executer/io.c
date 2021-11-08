/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   io.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkromer <jkromer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/03 12:15:10 by jkromer           #+#    #+#             */
/*   Updated: 2021/11/08 17:04:04 by jkromer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	set_pipe_io(t_cml *cml, t_exec *exec, int i)
{
	int	has_pipe;

	has_pipe = (cml[i + 1].line != NULL);
	if (has_pipe)
	{
		pipe(exec->pipe_fds[exec->nb_pipe]);
		exec->out = exec->pipe_fds[exec->nb_pipe][1];
	}
	if (i > 0)
		exec->in = exec->pipe_fds[abs(exec->nb_pipe - 1)][0];
	if (has_pipe)
	{
		exec->nb_pipe++;
		if (exec->nb_pipe > 1)
			exec->nb_pipe = 0;
	}
}

static int	set_redir_io(t_cml *cml, t_exec *exec, int i)
{
	while (cml[i].lst_redi)
	{
		if (cml[i].lst_redi->tkn->type == GREAT)
			set_trunc_file(cml, exec, i);
		else if (cml[i].lst_redi->tkn->type == DGREAT)
			set_append_file(cml, exec, i);
		else if (cml[i].lst_redi->tkn->type == LESS)
		{
			set_input_file(cml, exec, i);
			if (exec->in == -1)
				return (open_error(cml[i].lst_redi->tkn->word));
		}
		cml[i].lst_redi = cml[i].lst_redi->next;
	}
	return (1);
}

int	set_io(t_cml *cml, t_exec *exec, int i)
{
	exec->in = STDIN_FILENO;
	exec->out = STDOUT_FILENO;
	set_pipe_io(cml, exec, i);
	if (cml[i].lst_redi)
		return (set_redir_io(cml, exec, i));
	return (1);
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
