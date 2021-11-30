/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkromer <jkromer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/27 12:00:08 by jkromer           #+#    #+#             */
/*   Updated: 2021/11/30 12:30:28 by jkromer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTE_H
# define EXECUTE_H

t_list	*init_env(char **envp);
char	*search_path(const char *prog, t_list *env);
int		execute(char *const *args, t_exec *exec, t_cml *cml);
int		set_io(t_cml *cml, t_exec *exec, int i);
void	redirect_io(t_exec *exec);
void	reset_io(t_exec *exec);
void	set_trunc_file(const char *file, t_exec *exec);
void	set_append_file(const char *file, t_exec *exec);
void	set_input_file(const char *file, int type, t_exec *exec);
void	close_pipes(t_exec *exec);
void	init_pipes(t_exec *exec);
int		has_pipe(t_exec *exec);
void	wait_processes(t_exec *exec);
char	*get_full_path(char *arg, t_list *env);

#endif
