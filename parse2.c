/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tyuan <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/22 17:30:27 by tyuan             #+#    #+#             */
/*   Updated: 2021/10/22 17:30:31 by tyuan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	variable_expansion(t_token *tok)
{
	char	**tabs;
	char	**tab_q;
	int		*start;
	int		*end;
	int		ret;

	if (!(ret = num_of_vars(tok)))
		return ;
	if (!(tabs = malloc(sizeof(char *) * (ret * 2 + 2))) ||
		!(tab_q = malloc(sizeof(char *) * (ret * 2 + 2))) ||
		!(start = malloc(sizeof(int) * (ret + 1))) ||
		!(end = malloc(sizeof(int) * (ret + 1))))
		exit(0);//clean_exit("Failed to malloc");
	locate_vars_to_expand(tok, start, end);
	str_idx_split(tok->word, start, end, tabs);
	str_idx_split(tok->quoted, start, end, tab_q);
	ret = expand(tabs, tab_q);
	chang_token_value(tok, ret, combine_strings(tabs), combine_strings(tab_q));
	//free tab tabq start end.
}

int		locate_vars_to_expand(t_token *tok, int *start, int *end)
{
	int i;
	int n;

	i = 0;
	n = 0;
	while (tok->word[i])
	{
		if (tok->word[i] == '$' && tok->quoted[i] != SINGLE_QUOTED)
		{
			start[n] = i++;
			while (tok->word[i] && tok->word[i] != ' ' && tok->word[i] != '\''
					&& tok->word[i] != '"' && tok->word[i] != '$')
				i++;
			end[n++] = --i;
		}
		i++;
	}
	start[n] = -1;
	return (n);
}

int		expand(char **tabs, char **tab_q)
{
	char    *tmp;
	int     i;
	int     type;

	i = 0;
	type = WORD;
	while (tabs[i])
	{
		if (tabs[i][0] == '$')
		{
			tmp = tabs[i];
			tabs[i] = ft_strdup(getenv(&tabs[i][1]));
			free(tmp);
			tmp = tab_q[i];
			tab_q[i] = quoted_bit_reset(tabs[i], tab_q[i][0], &type);
			free(tmp);
		}
		i++;
	}
	return (type);
}

char    *quoted_bit_reset(char *line, char c, int *type)
{
	char    *quo;
	int     n;

	if (!(quo =  malloc(sizeof(char) * (ft_strlen(line) + 1))))
		exit (-1);
	while (line[n])
	{
		if (line[n] == ' ' && c == NQ)
			*type = UNQUOTED_SPACE;
		quo[n++] = c;
	}
	quo[n] = '\0';
	return (quo);
}

void 	var_space_splitting(t_list	*lst_token)
{
	char	**tabs;
	t_list	*cur;
	t_list	*nlst;
	t_list	*nlst_last;

	cur = lst_token;
	nlst = NULL;
	while (cur)
	{
		if (cur->content->type == UNQUOTED_SPACE)
		{
			tabs = jump_quotes_ft_split(cur->content->word, cur->content->quoted, ' ');
			chang_token_value(cur->content, WORD, *tabs++, NULL);
			while (*tabs)
				ft_lstadd_back(&nlst, ft_lstnew(new_token(WORD, *tabs++, NULL)));
			nlst_last = ft_lstlast(nlst);
			nlst_last->next = cur->next;
			cur->next = nlst;
			cur = nlst_last;
		}
		cur = cur->next;
	}
}

void set_argv(t_cml *cml)
{
	int		i;
	t_list	*lst;

	i = 0;
	lst = cml->lst_token;
	cml->argv = malloc(sizeof(char *) * (ft_lstsize(lst) + 1));
	while (lst)
	{
		cml->argv[i++] = ft_strdup(lst->content->word);
		lst = lst->next;
	}
	cml->argv[i] = NULL;
}
