/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tyuan <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/22 17:30:08 by tyuan             #+#    #+#             */
/*   Updated: 2021/11/09 17:17:25 by jkromer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* err msg: ambiguous redirect.*/
t_cml	*parse(char *line)
{
	t_cml	*cmls;
	int		n;

	cmls = parse_pipe(line);
	n = 0;
	while (cmls[n].line)
	{
		cmls[n].lst_redi = NULL;
		cmls[n].lst_token = NULL;
		set_token(&cmls[n]);
		tknlstiter(cmls[n].lst_token, &variable_expansion);
		tknlstiter(cmls[n].lst_token, &quote_removal);
		var_space_splitting(cmls[n].lst_token);
		set_argv(&cmls[n]);
		if (cmls[n].lst_redi)
		{
			tknlstiter(cmls[n].lst_redi, &variable_expansion);
			tknlstiter(cmls[n].lst_redi, &quote_removal);
			if (if_unquoted_space(cmls[n].lst_redi))
				exit (0);
		}
		n++;
	}
	return (cmls);
}

t_cml	*parse_pipe(char *line)
{
	char	**cml_tab;
	t_cml	*cmls;
	int		n;

	cml_tab = jump_quotes_ft_split(line, set_quoted_bits(line), '|');
	cmls = v_malloc(sizeof(t_cml) * (amount_of_cmls(cml_tab) + 1));
	n = 0;
	while (cml_tab[n])
	{
		cmls[n].line = ft_strdup(cml_tab[n]);
		n++;
	}
	cmls[n].line = NULL;
	//free_split(cml_tab);
	return (cmls);
}

void	set_token(t_cml *cml)
{
	char	**tabs;
	char	*quoted;
	char	*line;

	line = ft_strdup(cml->line);
	quoted = set_quoted_bits(line);
	parse_redirection(&cml->lst_redi, &line, &quoted);
	tabs = jump_quotes_ft_split(line, quoted, ' ');
	if (!(*tabs))
	{
		tknlstadd_back(&(cml->lst_token), tknlstnew(
				new_token(WORD, *tabs, set_quoted_bits(*tabs))));
	}
	while (*tabs)
	{
		tknlstadd_back(&(cml->lst_token), tknlstnew(
				new_token(WORD, *tabs, set_quoted_bits(*tabs))));
		tabs++;
	}
	free(quoted);
	//cleanup(tabs, line);
}

/*
* ct[0]: current char
* ct[1]: beinning of redirection operator
* ct[2]: beginning of path
* //need to make sure in syntax check that the line doest end with < > >>
*/
void	parse_redirection(t_tknlst **lst_redi, char **l, char **q)
{
	int		ct[3];

	ft_memset(ct, 0, sizeof(ct));
	while ((*l)[ct[0]])
	{
		if (((*l)[ct[0]] == '>' || (*l)[ct[0]] == '<') && (*q)[ct[0]] == NQ)
		{
			ct[1] = ct[0]++;
			if ((*l)[ct[0]] == '>')
				ct[0]++;
			while ((*l)[ct[0]] == ' ')
				ct[0]++;
			ct[2] = ct[0];
			while ((*l)[ct[0]] && (((*l)[ct[0]] != ' ' && (*l)[ct[0]] != '<' &&
				(*l)[ct[0]] != '>' && (*q)[ct[0]] == NQ) || (*q)[ct[0]] > NQ))
				ct[0]++;
			tknlstadd_back(lst_redi, tknlstnew(new_token(typeof_redi(&(*l)
						[ct[1]]), sh_substr(*l, ct[2], ct[0] - ct[2]),
						set_quoted_bits(sh_substr(*l, ct[2], ct[0] - ct[2])))));
			remove_substr(l, ct[1], ct[0] - 1);
			remove_substr(q, ct[1], ct[0] - 1);
			ct[0] = ct[1] - 1;
		}
		ct[0]++;
	}
}

void	quote_removal(t_token *tok)
{
	char	*tmp;
	int		i;
	int		j;

	if (!tok->word)
		return ;
	tmp = ft_strdup(tok->word);
	i = 0;
	j = 0;
	while (tmp[i])
	{
		if (tok->quoted[i] != QUOTATION_MARK)
		{
			tok->word[j] = tmp[i];
			tok->quoted[j++] = tok->quoted[i];
		}
		i++;
	}
	tok->word[j] = '\0';
	tok->quoted[j] = '\0';
	free(tmp);
}
