/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkromer <jkromer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/27 12:00:08 by jkromer           #+#    #+#             */
/*   Updated: 2021/11/06 10:16:56 by jkromer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTE_H
# define EXECUTE_H

typedef struct s_exec
{
	int		in;
	int		out;
	int		status;
	t_list	*env;
	pid_t	pids[256];
	int		pipe_fds[2][2];
	int		nb_ps;
	int		nb_pipe;
	int		saved_stdin;
	int		saved_stdout;
}			t_exec;

t_list	*init_env(char **envp);
int		execute(char *const *args, t_exec *exec);
char	*search_path(const char *prog);
void	set_io(t_cml *cml, t_exec *exec, int i);
void	redirect_io(t_exec *exec);
void	reset_io(t_exec *exec);

#endif
