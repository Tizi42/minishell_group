/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tool_heredoc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tyuan <tyuan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/12 09:31:47 by tyuan             #+#    #+#             */
/*   Updated: 2021/11/18 17:18:27 by jkromer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*available_heredoc_name(void)
{
	char	*filepath;
	int		n;
	char	*suffix;

	filepath = v_malloc(sizeof(char) * 30);
	*filepath = '\0';
	ft_strcat(filepath, "/tmp/msh-hd-0");
	n = 1;
	while (!access(filepath, F_OK) && n < 99999)
	{
		filepath[12] = '\0';
		suffix = ft_itoa(n++);
		ft_strcat(filepath, suffix);
		free(suffix);
	}
	return (filepath);
}

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

int	wait_heredoc(char *filepath)
{
	waitpid(g_sig.pid, g_sig.status, 0);
	g_sig.pid = -1;
	init_signals();
	if (WIFSIGNALED(*g_sig.status))
	{
		*g_sig.status = WTERMSIG(*g_sig.status) + 128;
		ft_putchar('\n');
		unlink(filepath);
		free(filepath);
		return (1);
	}
	free(filepath);
	return (0);
}
