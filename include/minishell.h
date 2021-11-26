/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tyuan <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/29 15:42:05 by tyuan             #+#    #+#             */
/*   Updated: 2021/11/26 12:58:47 by jkromer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <sys/wait.h>
# include <sys/errno.h>
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>
# include <stdlib.h>
# include <fcntl.h>
# include "libft.h"
# include "structs.h"
# include "parse.h"
# include "execute.h"
# include "builtins.h"
# include "error.h"

/* main.c */
void	ignore_sig(void);
void	close_std_fds(void);

/* clean.c */
void	clean_token(t_token *tok);
void	clean_tknlst(t_tknlst *lst);
void	*clean_cml(t_cml *cml);
void	cleanup(char **paths, char *new_prog);

/* tool.c */
void	*v_malloc(size_t size);
pid_t	v_fork(void);
int		str_contains_set(const char *str, const char *set);
char	*get_env_value(char *key, t_exec exec);
int		empty_line(char *line);

/* signals.c */
void	init_signals(void);
void	reset_quit_handler(void);
void	reset_int_handler(void);

/* init.c */
void	init_msh(t_exec *exec, char **envp);
void	init_pids(t_cml *cml, t_exec *exec);

extern struct s_sig	g_sig;

#endif
