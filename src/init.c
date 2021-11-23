#include "minishell.h"

t_exec	init_msh(char **envp)
{
	t_exec	exec;

	exec.status = 0;
	exec.env = init_env(envp);
	g_sig.pid = -1;
	g_sig.status = &exec.status;
	return (exec);
}

void	init_pids(t_cml *cml, t_exec *exec)
{
	int	i;

	i = 0;
	while (cml[i].line)
		i++;
	exec->pids = v_malloc(sizeof(pid_t) * i);
}
