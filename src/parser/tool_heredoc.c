/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tool_heredoc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tyuan <tyuan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/12 09:31:47 by tyuan             #+#    #+#             */
/*   Updated: 2021/11/18 16:32:22 by jkromer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*get_hd_n_path(int n)
{
	char	*filepath;
	char	*suffix;

	suffix = ft_itoa(n);
	filepath = sh_strjoin("/tmp/msh-hd-", suffix);
	free(suffix);
	return (filepath);
}

void	set_heredoc_path(t_cml *cmls)
{
	t_tknlst	*lst;
	int			n;
	char		*tmp;

	n = 0;
	while (cmls->line)
	{
		lst = cmls->lst_redi;
		while (lst)
		{
			if (lst->tkn->type == HEREDOC)
			{
				tmp = lst->tkn->word;
				lst->tkn->word = get_hd_n_path(n++);
				free(tmp);
			}
			lst = lst->next;
		}
		cmls++;
	}
}

int	wait_heredoc(const char *filepath)
{
	waitpid(g_sig.pid, g_sig.status, 0);
	g_sig.pid = 0;
	if (WIFSIGNALED(*g_sig.status))
	{
		*g_sig.status = WTERMSIG(*g_sig.status) + 128;
		unlink(filepath);
		return (1);
	}
	return (0);
}
