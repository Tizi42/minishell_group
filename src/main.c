#include <stdio.h>
#include <readline/readline.h>
#include "parse.h"
#include "execute.h"

int main(int ac, char **av, char **envp)
{
	char	*line;
	t_cml	*cml;
	t_list	*env;
	int		i;

	(void)ac;
	(void)av;
	line = readline("> ");
	cml = parse(line);
	env = init_env(envp);
	i = 0;
	while (cml[i].line)
	{
		execute(cml[i].argv, env);
		i++;
	}
	ft_lstclear(&env);
	free(line);
	free(cml);
}
