/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   io2.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkromer <jkromer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/08 16:28:47 by jkromer           #+#    #+#             */
/*   Updated: 2021/11/30 13:40:53 by jkromer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	set_trunc_file(const char *file, t_exec *exec)
{
	if (exec->out != STDOUT_FILENO)
		close(exec->out);
	exec->out = open(file, O_CREAT | O_WRONLY | O_TRUNC, 0644);
}

void	set_append_file(const char *file, t_exec *exec)
{
	if (exec->out != STDOUT_FILENO)
		close(exec->out);
	exec->out = open(file, O_CREAT | O_WRONLY | O_APPEND, 0644);
}

void	set_input_file(const char *file, int type, t_exec *exec)
{
	if (exec->in != STDIN_FILENO)
		close(exec->in);
	exec->in = open(file, O_RDONLY);
	if (type == HEREDOC)
		unlink(file);
}

void	init_pipes(t_exec *exec)
{
	exec->nb_pipe = 0;
	exec->pipe_fds[0][0] = -1;
	exec->pipe_fds[0][1] = -1;
	exec->pipe_fds[1][0] = -1;
	exec->pipe_fds[1][1] = -1;
}

void	close_pipes(t_exec *exec)
{
	int	i;
	int	j;

	i = 0;
	while (i <= 1)
	{
		j = 0;
		while (j <= 1)
		{
			if (exec->pipe_fds[i][j] != -1)
				close(exec->pipe_fds[i][j]);
			j++;
		}
		i++;
	}
	close(exec->saved_stdin);
	close(exec->saved_stdout);
}
