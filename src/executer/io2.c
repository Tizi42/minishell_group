/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   io2.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkromer <jkromer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/08 16:28:47 by jkromer           #+#    #+#             */
/*   Updated: 2021/11/22 17:40:16 by jkromer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	set_trunc_file(t_cml *cml, t_exec *exec, int i)
{
	if (exec->out != STDOUT_FILENO)
		close(exec->out);
	exec->out = open(cml[i].lst_redi->tkn->word,
			O_CREAT | O_WRONLY | O_TRUNC, 0644);
}

void	set_append_file(t_cml *cml, t_exec *exec, int i)
{
	if (exec->out != STDOUT_FILENO)
		close(exec->out);
	exec->out = open(cml[i].lst_redi->tkn->word,
			O_CREAT | O_WRONLY | O_APPEND, 0644);
}

void	set_input_file(t_cml *cml, t_exec *exec, int i)
{
	if (exec->in != STDIN_FILENO)
		close(exec->in);
	exec->in = open(cml[i].lst_redi->tkn->word, O_RDONLY);
	if (cml[i].lst_redi->tkn->type == HEREDOC)
		unlink(cml[i].lst_redi->tkn->word);
}

void	init_pipes(t_exec *exec)
{
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
