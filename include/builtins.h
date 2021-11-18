/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkromer <jkromer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/18 11:13:04 by jkromer           #+#    #+#             */
/*   Updated: 2021/11/18 17:50:40 by jkromer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

unsigned char	cd(const char *path);
unsigned char	pwd(void);
unsigned char	echo(char *const *args);
unsigned char	exit_builtin(char *const *args,	t_exec *exec, t_cml *cml);
unsigned char	export(char *const *args, t_list **env);
unsigned char	unset(char *const *args, t_list **env);
unsigned char	env_builtin(const t_list *env);
unsigned char	exec_builtins(char *const *args, t_exec *exec, t_cml *cml);
int				match_name(const char *name, char *var);
int				is_in_env(const char *arg, t_list **env);

#endif
