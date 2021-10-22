#include "minishell.h"

int     if_unquoted_space(t_list *lst)
{
	while (lst)
	{
		if (lst->content->type == UNQUOTED_SPACE)
			return (1);
		lst = lst->next;
	}
    return (0);
}

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
        set_token(&cmls[n]);
        ft_lstiter(cmls[n].lst_token, &variable_expansion);
        ft_lstiter(cmls[n].lst_token, &quote_removal);
        var_space_splitting(cmls[n].lst_token);
        set_argv(&cmls[n]);
        if (cmls[n].lst_redi)
        {
            ft_lstiter(cmls[n].lst_redi, &variable_expansion);
            ft_lstiter(cmls[n].lst_redi, &quote_removal);
            if (if_unquoted_space(cmls[n].lst_redi))
                exit (0); //ambiguous redirect.
        }
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
    char    *line;

    line = ft_strdup(cml->line);
    quoted = set_quoted_bits(line);
    parse_redirection(&cml->lst_redi, &line, &quoted);
    tabs = jump_quotes_ft_split(line, quoted, ' ');
    if (!(*tabs))
    {
        ft_lstadd_back(&(cml->lst_token), ft_lstnew(
            new_token(WORD, *tabs, set_quoted_bits(*tabs))));
    }
    while (*tabs)
    {
        ft_lstadd_back(&(cml->lst_token), ft_lstnew(
            new_token(WORD, *tabs, set_quoted_bits(*tabs))));
        tabs++;
    }
    free(line);
}

/*
* ct[0]: current char
* ct[1]: beinning of redirection operator
* ct[2]: beginning of path
*/
void    parse_redirection(t_list **lst_redi, char **line, char **quoted)
{
    int     ct[3];

    ft_memset(ct, 0, sizeof(ct));
    while ((*line)[ct[0]])
    {
        if (((*line)[ct[0]] == '>' || (*line)[ct[0]] == '<') && (*quoted)[ct[0]] == NQ)
        {
            ct[1] = ct[0]++;
            if ((*line)[ct[0]] == '>')
                ct[0]++;
            while ((*line)[ct[0]] == ' ') //need to make sure in syntax check that the line doest end with < > >>
                ct[0]++;
            ct[2] = ct[0];
            while ((*line)[ct[0]] && (((*line)[ct[0]] != ' ' && (*quoted)[ct[0]] == NQ) || ((*quoted)[ct[0]] > NQ)))
                ct[0]++;
            ft_lstadd_back(lst_redi, ft_lstnew(new_token(typeof_redi(&(*line)[ct[1]]), 
                    ft_substr(*line, ct[2], ct[0] - ct[2]), 
                    set_quoted_bits(ft_substr(*line, ct[2], ct[0] - ct[2])))));
            remove_substr(line, ct[1], ct[0] - 1);
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
