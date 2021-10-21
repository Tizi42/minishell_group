#include "minishell.h"

t_token *new_token(int type, char *nword, char *nquo)
{
    t_token *new;

    if (!(new = malloc(sizeof(t_token))))
        exit(0);
    new->type = type;
    new->word = nword;
    if (nquo == NULL)
        nquo = be_not_quoted(nword);
    new->quoted = nquo;
    return (new);
}

void    chang_token_value(t_token *tok, int type, char *nword, char *nquo)
{
    char    *tmp;
    int     i;

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

char    *be_not_quoted(char *w)
{
    char    *quo;
    int     i;

    if (!(quo =  malloc(sizeof(char) * (ft_strlen(w) + 1))))
        exit (-1);
    i = 0;
    while (w[i])
        quo[i++] = NQ; 
    quo[i] = '\0';
    return (quo);
}

char    *set_quoted_bits(char *line)
{
    char	*quoted;
    int		n;

    quoted = malloc(sizeof(char) * (ft_strlen(line) + 1));
    n = 0;
    while (line[n])
    {
        if (line[n] == '\'')
		{
			quoted[n++] = QUOTATION_MARK;
			while (line[n] && line[n] != '\'')
				quoted[n++] = SINGLE_QUOTED;
			quoted[n++] = QUOTATION_MARK;
		}
        else if (line[n] == '"')
        {
			quoted[n++] = QUOTATION_MARK;
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

int     typeof_redi(char *line)
{
    if (*line == '>')
    {
        if (*(line + 1) == '>')
            return (DGREAT);
        return (GREAT);
    }
    if (*line == '<')
        return (LESS);
    return (-1);
}