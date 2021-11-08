/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   io2.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkromer <jkromer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/08 16:28:47 by jkromer           #+#    #+#             */
/*   Updated: 2021/11/08 17:03:45 by jkromer          ###   ########.fr       */
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
}