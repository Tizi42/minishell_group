/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tool_token.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tyuan <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/22 17:31:03 by tyuan             #+#    #+#             */
/*   Updated: 2021/11/03 10:35:37 by jkromer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*new_token(int type, char *nword, char *nquo)
{
	t_token	*new;

	new = v_malloc(sizeof(t_token));
	new->type = type;
	new->word = nword;
	if (nquo == NULL)
		nquo = be_not_quoted(nword);
	new->quoted = nquo;
	return (new);
}

void	change_token_value(t_token *tok, int type, char *nword, char *nquo)
{
	char	*tmp;

	tok->type = type;
	tmp = tok->word;
	tok->word = nword;
	free(tmp);
	if (nquo == NULL)
		nquo = be_not_quoted(nword);
	tmp = tok->quoted;
	tok->quoted = nquo;
	free(tmp);
}

char	*be_not_quoted(char *w)
{
	char	*quo;
	int		i;

	if (!w)
		return (NULL);
	quo = v_malloc(sizeof(char) * (ft_strlen(w) + 1));
	i = 0;
	while (w[i])
		quo[i++] = NQ;
	quo[i] = '\0';
	return (quo);
}

char	*set_quoted_bits(char *line)
{
	char	*quoted;
	int		n;

	quoted = v_malloc(sizeof(char) * (ft_strlen(line) + 1));
	n = 0;
	while (line && line[n])
	{
		if (line[n] == '\'' || line[n] == '"')
		{
			quoted[n++] = QUOTATION_MARK;
			if (line[n - 1] == '\'')
				while (line[n] && line[n] != '\'')
					quoted[n++] = SINGLE_QUOTED;
			else if (line[n - 1] == '"')
				while (line[n] && line[n] != '"')
					quoted[n++] = DOUBLE_QUOTED;
			quoted[n++] = QUOTATION_MARK;
		}
		else
			quoted[n++] = NQ;
	}
	quoted[n] = '\0';
	return (quoted);
}

char	*quoted_bit_reset(char *line, char c, int *type)
{
	char	*quo;
	int		n;

	quo = v_malloc(sizeof(char) * (ft_strlen(line) + 1));
	n = 0;
	while (line[n])
	{
		if (line[n] == ' ' && c == NQ)
			*type = UNQUOTED_SPACE;
		quo[n++] = c;
	}
	quo[n] = '\0';
	return (quo);
}
