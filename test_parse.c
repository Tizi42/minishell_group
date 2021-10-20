#include "minishell.h"

int main(int ac, char **av)
{
	char *line;
    t_cml *cml;
    int i;

	while (1)
	{
		line = readline(">");
		cml = parse(line);
        i = 0;
        while (*cml->argv)
            printf("%d: %s\n", i++, *cml->argv++);
		free(line);
	}
	return (0);
}