#include "minishell.h"

t_cml    *parse(char *line)
{
    t_cml   *cmls;
    int     n;

    cmls = parse_pipe(line);
    cmls->lst_redi = NULL;
    cmls->lst_token = NULL;
    n = 0;
    while (cmls[n].line)
    {
        printf("A\n");
        set_token(&cmls[n]);
        printf("Atok: %s\n", cmls[n].lst_token->content->word);
		ft_lstiter(cmls[n].lst_token, &quote_removal);
        printf("Btok: %s\n", cmls[n].lst_token->content->word);
        ft_lstiter(cmls[n].lst_token, &variable_expansion);
        printf("Ctok: %s\n", cmls[n].lst_token->content->word);
        var_space_splitting(cmls[n].lst_token);
        printf("Dtok: %s\n", cmls[n].lst_token->content->word);
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
    if (!(cmls = malloc(sizeof(t_cml) * ( amount_of_cmls(cml_tab) + 1))))
        exit(0);//clean_exit("Failed to malloc.");
    n = 0;
    while (cml_tab[n])
    {
        cmls[n].line = ft_strdup(cml_tab[n]);
        n++;
    }
    cmls[n].line = NULL;
    free(cml_tab);
    return (cmls);
}

void    set_token(t_cml *cml)
{
    char    **tabs;
    char    *quoted;

    quoted = set_quoted_bits(cml->line);
    parse_redirection(cml, &quoted);
    tabs = jump_quotes_ft_split(cml->line, quoted, ' ');
    while (*tabs)
    {
        ft_lstadd_back(&(cml->lst_token), ft_lstnew(
            new_token(WORD, *tabs, set_quoted_bits(*tabs))));
        tabs++;
    }
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
			tok->word[j] = tmp[i];
			tok->quoted[j++] = tok->quoted[i];
		}
		i++;
	}
	tok->word[j] = '\0';
    tok->quoted[j] = '\0';
	free(tmp);
}
