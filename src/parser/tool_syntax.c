/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tool_syntax.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tyuan <tyuan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/10 18:21:51 by tyuan             #+#    #+#             */
/*   Updated: 2021/11/10 18:22:00 by tyuan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	unclosed_quot_mrks(char *line, char **p)
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

static int	if_redi_error(char *line, char **p)
{
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
		if (!*line || *line == '<' || *line == '>' || *line == '|')
			return (1);
	}
	*p = line - 1;
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

int	check_syntax(char *line)
{
	if (str_start_with(line, '|'))
	{
		syntax_error("unexpected token `|'");
		return (0);
	}
	while (*line)
	{
		if ((*line == '\'' || *line == '"') && unclosed_quot_mrks(line, &line))
				return (0);
		else if ((*line == '>' || *line == '<') && if_redi_error(line, &line))
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
