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
				printf("redi:type:%i, word:%s\n", lst->content->type, lst->content->word);
				lst = lst->next;
			}
			n++;
		}
		free(line);
	}
	return (0);
}