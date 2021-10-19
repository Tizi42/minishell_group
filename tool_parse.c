#include "minishell.h"

int    *set_quoted_bits(char *line)
{
    char	*quoted;
    int		n;

    quoted = malloc(sizeof(int) * (ft_strlen(line) + 1));
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
}

void    remove_substr(char **line, int sub_start, int sub_end)
{
    char *tmp;

    if (!line || !*line || sub_end < sub_start)
        return ;
    tmp = *line;
    tmp[sub_start] = '\0';
    *line = ft_strjoin(tmp, &tmp[sub_end + 1]);
    free(tmp);
}

char	*combine_strings(char **tab)
{
	char	*newl;
	int		len;
	int		j;

	len = 0;
	j = 0;
	while (tab[j])
		len += ft_strlen(*tab[j++]);
	if (!(newl = malloc(sizeof(char) * (len + 1))))
		clean_exit("Failed to malloc.");
	*newl = '\0';
	j = 0;
	while (tab[j])
		newl = ft_strlcat(newl, tab[j++], len);
	return (newl);
}

void	str_idx_split(char *l, int *start, int *end, char **tab)
{
	int i;
	int n;

	i = 0;
	n = 0;
	if (start[0] > 0)
		tab[n++] = ft_substr(l, 0, start[0]);
	while (start[i] > 0)
	{
		tab[n++] = ft_substr(l, start[i], end[i] - start[i] + 1);
		if (l[end[i] + 1])
			if (start[i + 1] > 0)
				tab[n++] = ft_substr(l, end[i] + 1, start[i + 1] - end[i] - 1);
			else
				tab[n++] = ft_strdup(&l[end[i] + 1]);
		i++;
	}
	tab[n] = NULL;
}

int     num_of_vars(t_cml *tok)
{
    int i;
    int n;

    i = 0;
    n = 0;
    while (tok->word[i])
	{
		if (tok->word[i] == '$' && tok->quoted[i] != SINGLE_QUOTED)
            n++;
        i++;
	}
    return (n);
}