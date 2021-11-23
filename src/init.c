/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tyuan <tyuan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 18:07:04 by tyuan             #+#    #+#             */
/*   Updated: 2021/11/23 18:07:07 by tyuan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
