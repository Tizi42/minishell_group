/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tyuan <tyuan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/11 23:59:41 by tyuan             #+#    #+#             */
/*   Updated: 2021/11/18 17:19:13 by jkromer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*str_variable_expansion(char *line, t_exec exec, int n)
{
	char	**tabs;
	int		*start;
	int		*end;
	char	*ret;
	t_token	*tok;

	tok = new_token(WORD, line, NULL);
	n = num_of_vars(tok);
	if (!n)
		ret = ft_strdup(line);
	else
	{
		tabs = v_malloc(sizeof(char *) * (n * 2 + 2));
		start = v_malloc(sizeof(int) * (n + 1));
		end = v_malloc(sizeof(int) * (n + 1));
		locate_vars_to_expand(tok, start, end);
		str_idx_split(tok->word, start, end, tabs);
		str_expand(tabs, exec);
		ret = combine_strings(tabs);
		free_split(tabs);
		free(start);
		free(end);
	}
	clean_token(tok);
	return (ret);
}

void	str_expand(char **tabs, t_exec exec)
{
	int		i;
	char	*tmp;

	i = 0;
	while (tabs[i])
	{
		if (tabs[i][0] == '$')
		{
			tmp = tabs[i];
			if (!tabs[i][1])
				tabs[i] = ft_strdup("$");
			else
				tabs[i] = get_env_value(&tabs[i][1], exec);
			free(tmp);
		}
		i++;
	}
}

void	heredoc_cprocess(char *filepath, char *delim, int expand, t_exec exec)
{
	int		fd;
	char	*line;

	fd = open(filepath, O_WRONLY | O_CREAT | O_TRUNC, 0600);
	if (fd == -1)
		unix_error(filepath);
	reset_int_handler();
	line = readline("> ");
	while (line && ft_strcmp(delim, line))
	{
		if (expand)
			line = str_variable_expansion(line, exec, 0);
		write(fd, line, ft_strlen(line));
		write(fd, "\n", 1);
		free(line);
		line = readline("> ");
	}
	close(fd);
	if (!line)
		ft_puts("msh: warning: here-document delimited by end-of-file");
	free(line);
	exit(0);
}

int	creat_heredoc(char *delim, int expand, t_exec exec)
{
	char	*filepath;

	filepath = available_heredoc_name();
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, SIG_IGN);
	g_sig.pid = v_fork();
	if (g_sig.pid == 0)
		heredoc_cprocess(filepath, delim, expand, exec);
	free(delim);
	return (wait_heredoc(filepath));
}

char	*check_heredoc(char *operator, char *line, t_exec exec)
{
	int		n;
	int		expand;
	char	*pos;

	n = 0;
	expand = 1;
	if (*operator != '<' || *(operator + 1) != '<')
		return (line - 1);
	while (line[n] && !ft_contains(" |<>", line[n]))
	{
		if (ft_contains("'\"", line[n]))
		{
			expand = 0;
			pos = line;
			if (unclosed_quot_mrks(&line[n], &pos))
				return (NULL);
			n = pos - line;
		}
		n++;
	}
	if (creat_heredoc(str_quote_removal(ft_strndup(line, n)), expand, exec))
		return (NULL);
	return (&line[n - 1]);
}
