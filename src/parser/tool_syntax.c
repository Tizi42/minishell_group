/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tool_syntax.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tyuan <tyuan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/10 18:21:51 by tyuan             #+#    #+#             */
/*   Updated: 2021/11/11 13:56:07 by jkromer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	unclosed_quot_mrks(char *line, char **p)
{
	char	mark;

	if (*line == '\'' || *line == '"')
	{
		mark = *(line++);
		while (*line && *line != mark)
			line++;
		if (*line != mark)
		{
			syntax_error("found unclosed question mark");
			return (1);
		}
	}
	*p = line;
	return (0);
}

static int	if_redi_error(char *line, char **p, t_exec exec)
{
	char	*operator;

	operator = line;
	if (*line == '>' || *line == '<')
	{
		if (*(line + 1) == *line)
			line++;
		line++;
		while (*line == ' ')
			line++;
		if (!*line)
			syntax_error("unexpected token `newline'");
		else if (*line == '<')
			syntax_error("unexpected token `<'");
		else if (*line == '>')
			syntax_error("unexpected token `>'");
		else if (*line == '|')
			syntax_error("unexpected token `|'");
		if (!*line || ft_contains("<>|", *line))
			return (1);
	}
	*p = check_here_doc(operator, line, exec);
	if (!*p)
		return (1);
	return (0);
}

static int	empty_between_pipe(char *line, char **p)
{
	if (*line == '|')
	{
		line++;
		while (*line == ' ')
			line++;
		if (*line == '|')
		{
			syntax_error("unexpected token `|'");
			return (1);
		}
	}
	*p = line - 1;
	return (0);
}

int	check_syntax(char *line, t_exec exec)
{
	if (str_start_with(line, '|'))
	{
		syntax_error("unexpected token `|'");
		return (0);
	}
	while (*line)
	{
		if (ft_contains("'\"", *line) && unclosed_quot_mrks(line, &line))
			return (0);
		else if (ft_contains("<>", *line) && if_redi_error(line, &line, exec))
			return (0);
		else if (*line == '|' && empty_between_pipe(line, &line))
			return (0);
		line++;
	}
	if (str_end_with(line, '|'))
	{
		syntax_error("command should not end with token `|'");
		return (0);
	}
	return (1);
}
