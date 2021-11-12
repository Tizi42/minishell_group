/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tool_parse2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tyuan <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/22 17:30:55 by tyuan             #+#    #+#             */
/*   Updated: 2021/10/22 17:31:30 by tyuan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_cml(t_cml *cmls)
{
	cmls->lst_redi = NULL;
	cmls->lst_token = NULL;
	cmls->line = NULL;
	cmls->argv = NULL;
}

int	amount_of_cmls(char **cml_tab)
{
	int	n;

	n = 0;
	if (!cml_tab)
		return (0);
	while (cml_tab[n])
		n++;
	return (n);
}

int	num_of_vars(t_token *tok)
{
	int	i;
	int	n;

	i = 0;
	n = 0;
	if (!tok->word)
		return (0);
	while (tok->word[i])
	{
		if (tok->word[i] == '$' && tok->quoted[i] != SINGLE_QUOTED)
			n++;
		i++;
	}
	return (n);
}

int	if_unquoted_space_in_redi(t_tknlst *lst)
{
	while (lst)
	{
		if (lst->tkn->type == UNQUOTED_SPACE)
		{
			syntax_error("ambiguous redirect");
			return (1);
		}
		lst = lst->next;
	}
	return (0);
}

int	typeof_redi(char *line)
{
	if (*line == '>')
	{
		if (*(line + 1) == '>')
			return (DGREAT);
		return (GREAT);
	}
	if (*line == '<')
	{
		if (*(line + 1) == '<')
			return (HEREDOC);
		return (LESS);
	}
	return (-1);
}
