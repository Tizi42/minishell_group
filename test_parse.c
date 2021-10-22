/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_parse.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tyuan <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/22 17:30:35 by tyuan             #+#    #+#             */
/*   Updated: 2021/10/22 17:31:16 by tyuan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int main(int ac, char **av)
{
	char *line;
    t_cml *cml;
    int i;
	t_list *lst;

	while (1)
	{
		line = readline(">");
		cml = parse(line);
		int n = 0;
		while (cml[n].line)
		{
			i = 0;
			while (*(cml[n].argv))
			printf("%d: %s\n", i++, *(cml[n].argv++));
			lst = cml[n].lst_redi;
			while (lst)
			{
				printf("redi:type:%i, word:%s\n", lst->tkn->type, lst->tkn->word);
				lst = lst->next;
			}
			n++;
		}
		free(line);
	}
	return (0);
}
