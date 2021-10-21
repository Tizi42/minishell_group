#include "minishell.h"

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

char	*combine_strings(char **tabs)
{
	char	*newl;
	int		len;
	int		j;

	len = 0;
	j = 0;
	while (tabs[j])
		len += ft_strlen(tabs[j++]);
	if (!(newl = malloc(sizeof(char) * (len + 1))))
		exit(0);//clean_exit("Failed to malloc.");
	*newl = '\0';
	j = 0;
	while (tabs[j])
		ft_strlcat(newl, tabs[j++], len);
	return (newl);
}

void	str_idx_split(char *l, int *start, int *end, char **tabs)
{
	int i;
	int n;

	i = 0;
	n = 0;
	if (start[0] > 0)
		tabs[n++] = ft_substr(l, 0, start[0]);
	while (start[i] > 0)
	{
		tabs[n++] = ft_substr(l, start[i], end[i] - start[i] + 1);
		if (l[end[i] + 1])
		{
			if (start[i + 1] > 0)
				tabs[n++] = ft_substr(l, end[i] + 1, start[i + 1] - end[i] - 1);
			else
				tabs[n++] = ft_strdup(&l[end[i] + 1]);
		}
		i++;
	}
	tabs[n] = NULL;
}

int     num_of_vars(t_token *tok)
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

int		amount_of_cmls(char **cml_tab)
{
	int n;

	n = 0;
	if (!cml_tab)
		return (0);
	while (cml_tab[n])
		n++;
	return (n);
}