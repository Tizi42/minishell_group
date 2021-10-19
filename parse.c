#include "minishell.h"

t_cml    *parse(char *line)
{
    t_cml   *cmls;
    int     n;

    cmls = parse_pipe(line);
    n = 0;
    while (cmls[n])
    {
        set_token(&cmls[n]);
		ft_lstiter(cmls[n].lst_token, quote_removal);
        ft_lstiter(cmls[n].lst_token, variable_expansion);
        var_space_splitting(cmls[n].lst_token);
        set_argv(&cmls[n]);
        n++;
    }
    return (cmls);
}

t_cml   *parse_pipe(char *line)
{
    char    **cml_tab;
    t_cml   *cmls;
    int     n;

    cml_tab = jump_quotes_ft_split(line, set_quoted_bits(line), '|');
    if (!(cmls = malloc(sizeof(t_cml) * ( amount_of_cmls(cmls) + 1))))
        clean_exit("Failed to malloc.");
    n = 0;
    while (cml_tab[n])
    {
        cmls[n].line = ft_strdup(cml_tab[n]);
        n++;
    }
    cmls[n] = NULL;
    free(cml_tab);
    return (cmls);
}

void    set_token(t_cml *cml)
{
    char    **tab;
    int     *quoted;

    quoted = set_quoted_bits(cml->line);
    parse_redirection(cml, &quoted);
    tab = jump_quotes_ft_split(cml->line, quoted, ' ');
    while (*tab)
        ft_lstadd_back(&(cml->lst_token), ft_lstnew(
            new_token(WORD, *tab, set_quoted_bits(*tab++))));
}

/*
* ct[0]: current char
* ct[1]: beinning of redirection operator
* ct[2]: beginning of path
*/
void    parse_redirection(t_cml *cml, char **quoted)
{
    int     ct[3];

    ft_memset(ct, 0, sizeof(ct));
    while (cml->line[ct[0]])
    {
        if (*quoted[ct[0]] == NQ && (cml->line[ct[0]] == '>' || cml->line[ct[0]] == '<'))
        {
            ct[1] = ct[0]++;
            if (cml->line[ct[0]] == '>')
                ct[0]++;
            while (cml->line[ct[0]] == ' ') //need to make sure in syntax check that the line doest end with < > >>
                ct[0]++;
            ct[2] = ct[0];
            while (cml->line[ct[0]] && cml->line[ct[0]] != ' ' && *quoted[ct[0]] == NQ)
                ct[0]++;
            ft_lstadd_back(&(cml->lst_redi), ft_lstnew(new_token(typeof_redi(&cml->line[ct[1]]), ft_substr(cml->line, ct[2], ct[0] - ct[2]), NULL)));
            remove_substr(&cml->line, ct[1], ct[0] - 1);
            remove_substr(quoted, ct[1], ct[0] - 1);
            ct[0] = ct[1] - 1;
        }
        ct[0]++;
    }
}

/*int		split_and_expand(char *l, char *q, char **tab, char **tab_q)
{
	int i;
	int j;

	i = 0;
	j = 0;
	while (l[i])
	{
		if (l[i] == '$' && q[i] != SINGLE_QUOTED)
		{
			if (i != 0)
			{
				tab[j] = ft_substr(l, 0, i);
				tab_q[j++] = ft_substr(q, 0, i);
			}
			i += parse_variable(&l[i], &q[i], &tab[j], &tab_q[j++]);
			l = &l[i];
			q = &q[i];
			i = -1;
		}
		i++;
	}
	//
	if (i != 0)
	{
		tab[j] = strdup(cp);
		tab_q[j++] = strdup(cp_q);
	}
	tab[j] = NULL;
	tab_q[j] = NULL;

	//if (if_unquoted_space())
	//	type = UNQUOTED_SPACE;
	return (type);
}*/

void    quote_removal(t_token *tok)
{
	char	*tmp;
	int		i;
	int		j;

	tmp = ft_strdup(tok->word);
	i = 0;
	j = 0;
	while (tmp[i])
	{
		if (tok->quoted[i] != QUOTATION_MARK)
		{
			tok->word[j++] = tmp[i];
			tok->quoted[j++] = tok->quoted[i];
		}
		i++;
	}
	tok->word[j] = '\0';
	free(tmp);
}
