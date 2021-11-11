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

char	*str_variable_expansion(char *line, t_exec exec)
{
	char	**tabs;
	int		*start;
	int		*end;
	int		ret;
	t_token	*tok;

	tok = new_token(WORD, line, NULL);
	ret = num_of_vars(tok);
	if (!ret)
		return (line);
	tabs = v_malloc(sizeof(char *) * (ret * 2 + 2));
	start = v_malloc(sizeof(int) * (ret + 1));
	end = v_malloc(sizeof(int) * (ret + 1));
	locate_vars_to_expand(tok, start, end);
	str_idx_split(tok->word, start, end, tabs);
	str_expand(tabs, exec);
	chang_token_value(tok, WORD, combine_strings(tabs), NULL);
	cleanup(tabs, (char *)start);
	free(end);
	return (tok->word);
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

void	creat_here_doc(char *delim, int expand, t_exec exec)
{
	char	*filepath;
	char	*line;
	int		fd;

	filepath = available_heredoc_name();
	fd = open(filepath, O_WRONLY|O_CREAT|O_TRUNC, 0600);
	if (fd == -1)
		exit(-1) ; //clean_exit();
	line = readline("> ");
	while (line && ft_strcmp(delim, line))
	{
		if (expand)
			line = str_variable_expansion(line, exec);
		write(fd, line, ft_strlen(line));
		write(fd, "\n", 1);
		free(line);
		line = readline("> ");
	}
	if (line)
		free(line);
	close(fd);
	free(delim);
	free(filepath);
}

char	*check_here_doc(char *operator, char *line, t_exec exec)
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
	creat_here_doc(str_quote_removal(ft_strndup(line, n)), expand, exec);
	return (&line[n - 1]);
}
