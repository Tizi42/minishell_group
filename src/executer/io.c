/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   io.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkromer <jkromer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/03 12:15:10 by jkromer           #+#    #+#             */
/*   Updated: 2021/11/03 16:16:56 by jkromer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	set_io(t_cml *cml, t_exec *exec, int i)
{
	static int	fd[2];

	exec->in = STDIN_FILENO;
	exec->out = STDOUT_FILENO;
	if (cml[i + 1].line)
	{
		pipe(fd);
		exec->out = fd[1];
	}
	if (i > 0) {
		exec->in = fd[0];
	}
	printf("command: [%s]\nin = %d\nout = %d\n\n", cml[i].line, exec->in, exec->out);
}

void	redirect_io(t_exec exec)
{
	dup2(exec.in, STDIN_FILENO);
	dup2(exec.out, STDOUT_FILENO);
}
