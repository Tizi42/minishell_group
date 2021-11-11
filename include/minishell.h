/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tyuan <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/29 15:42:05 by tyuan             #+#    #+#             */
/*   Updated: 2021/11/11 19:22:58 by jkromer          ###   ########.fr       */
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

/* tool.c */
void	*v_malloc(size_t size);
void	cleanup(char **paths, char *new_prog);
char	*get_env_value(char *key, t_exec exec);
void	init_signals(void);
void	reset_quit_handler(void);
int		str_contains_set(const char *str, const char *set);

extern struct s_sig	g_sig;

#endif
