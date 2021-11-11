/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tyuan <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/22 17:30:27 by tyuan             #+#    #+#             */
/*   Updated: 2021/11/03 10:27:54 by jkromer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	variable_expansion(t_token *tok, t_exec *exec)
{
	char	**tabs;
	char	**tab_q;
	int		*start;
	int		*end;
	int		ret;

	ret = num_of_vars(tok);
	if (!ret)
		return ;
	tabs = v_malloc(sizeof(char *) * (ret * 2 + 2));
	tab_q = v_malloc(sizeof(char *) * (ret * 2 + 2));
	start = v_malloc(sizeof(int) * (ret + 1));
	end = v_malloc(sizeof(int) * (ret + 1));
	locate_vars_to_expand(tok, start, end);
	str_idx_split(tok->word, start, end, tabs);
	str_idx_split(tok->quoted, start, end, tab_q);
	ret = expand(tabs, tab_q, *exec);
	chang_token_value(tok, ret, combine_strings(tabs), combine_strings(tab_q));
	cleanup(tabs, (char *)start);
	cleanup(tab_q, (char *)end);
}

int	locate_vars_to_expand(t_token *tok, int *start, int *end)
{
	int	i;
	int	n;

	i = 0;
	n = 0;
	while (tok->word[i])
	{
		if (tok->word[i] == '$' && tok->quoted[i] != SINGLE_QUOTED)
		{
			start[n] = i++;
			if (tok->word[i] == '?')
				end[n++] = i;
			else
			{
				while (tok->word[i] && (ft_isalnum(tok->word[i])
						|| tok->word[i] == '_'))
					i++;
				end[n++] = --i;
			}
		}
		i++;
	}
	start[n] = -1;
	return (n);
}

int	expand(char **tabs, char **tab_q, t_exec exec)
{
	char	*tmp;
	int		i;
	int		type;

	i = 0;
	type = WORD;
	while (tabs[i])
	{
		if (tabs[i][0] == '$')
		{
			tmp = tabs[i];
			if (!tabs[i][1] && (tab_q[i][0] == DOUBLE_QUOTED || !tabs[i + 1]
				|| (tabs[i + 1] && tab_q[i + 1][0] != QUOTATION_MARK)))
				tabs[i] = ft_strdup("$");
			else
				tabs[i] = get_env_value(&tabs[i][1], exec);
			free(tmp);
			tmp = tab_q[i];
			tab_q[i] = quoted_bit_reset(tabs[i], tab_q[i][0], &type);
			free(tmp);
		}
		i++;
	}
	return (type);
}

void	var_space_splitting(t_tknlst *lst_token)
{
	char		**tabs;
	t_tknlst	*cur;
	t_tknlst	*nlst;
	t_tknlst	*nlst_last;

	cur = lst_token;
	nlst = NULL;
	while (cur)
	{
		if (cur->tkn->type == UNQUOTED_SPACE)
		{
			tabs = jump_quotes_ft_split(cur->tkn->word, cur->tkn->quoted, ' ');
			chang_token_value(cur->tkn, WORD, *tabs++, NULL);
			while (*tabs)
				tknlstadd_back(&nlst, tknlstnew(
						new_token(WORD, *tabs++, NULL)));
			nlst_last = tknlstlast(nlst);
			nlst_last->next = cur->next;
			cur->next = nlst;
			cur = nlst_last;
		}
		cur = cur->next;
	}
}

void	set_argv(t_cml *cml)
{
	int			i;
	t_tknlst	*lst;

	i = 0;
	lst = cml->lst_token;
	cml->argv = v_malloc(sizeof(char *) * (tknlstsize(lst) + 1));
	while (lst)
	{
		cml->argv[i++] = ft_strdup(lst->tkn->word);
		lst = lst->next;
	}
	cml->argv[i] = NULL;
}
