#include "minishell.h"

void	clean_token(t_token *tok)
{
	if (tok)
	{
		if (tok->word)
			free(tok->word);
		if (tok->quoted)
			free(tok->quoted);
		free(tok);
	}
}

void	clean_tknlst(t_tknlst *lst)
{
	t_tknlst	*next;
	t_tknlst	*cur;

	cur = lst;
	while (cur)
	{
		next = cur->next;
		clean_token(cur->tkn);
		free(cur);
		cur = next;
	}
}

void	clean_cml(t_cml *cml)
{
	t_cml	*cur;
	t_cml	*next;

	cur = cml;
	while (cur)
	{
		next = cur++;
		if (cur->line)
			free(cur->line);
		if (cur->argv)
			free_split(cur->argv);
		free(cur->lst_token);
		free(cur->lst_redi);
		free(cur);
		cur = next;
	}
}

void	cleanup(char **paths, char *new_prog)
{
	free(new_prog);
	free_split(paths);
}
