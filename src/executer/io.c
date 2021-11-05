/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   io.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkromer <jkromer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/03 12:15:10 by jkromer           #+#    #+#             */
/*   Updated: 2021/11/05 12:52:45 by jkromer          ###   ########.fr       */
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
	printf("command: [%s]\nin  = %d\nout = %d\n\n", cml[i].line, exec->in, exec->out);
}

void	redirect_io(t_exec *exec)
{
	int	i;

	if (exec->in != STDIN_FILENO)
		dup2(exec->in, STDIN_FILENO);
	if (exec->out != STDOUT_FILENO)
		dup2(exec->out, STDOUT_FILENO);
	i = 0;
	while (i < exec->nb_pipe)
	{
		close(exec->pipe_fds[i][0]);
		close(exec->pipe_fds[i][1]);
		i++;
	}
}
