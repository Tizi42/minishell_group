/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tyuan <tyuan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 18:07:04 by tyuan             #+#    #+#             */
/*   Updated: 2021/11/30 13:40:33 by jkromer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_msh(t_exec *exec, char **envp)
{
	exec->status = 0;
	exec->env = init_env(envp);
	g_sig.pid = -1;
	g_sig.status = &exec->status;
}

void	init_pids(t_cml *cml, t_exec *exec)
{
	int	i;

	exec->nb_ps = 0;
	i = 0;
	while (cml[i].line)
		i++;
	exec->pids = v_malloc(sizeof(pid_t) * i);
}
