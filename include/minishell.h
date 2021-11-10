/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tyuan <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/29 15:42:05 by tyuan             #+#    #+#             */
/*   Updated: 2021/11/08 11:46:36 by jkromer          ###   ########.fr       */
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

typedef struct s_token
{
	int		type;
	char	*word;
	char	*quoted;
}			t_token;

typedef struct s_tknlst
{
	t_token			*tkn;
	struct s_tknlst	*next;
}					t_tknlst;

typedef struct s_cml
{
	char		*line;
	t_tknlst	*lst_token;
	t_tknlst	*lst_redi;
	char		**argv;
}				t_cml;

typedef struct s_exec
{
	int		in;
	int		out;
	int		status;
	t_list	*env;
	pid_t	pids[256]; // maybe linked list ?
	int		pipe_fds[2][2];
	int		nb_ps;
	int		nb_pipe;
	int		saved_stdin;
	int		saved_stdout;
}			t_exec;

# include "parse.h"
# include "execute.h"
# include "builtins.h"
# include "error.h"

/* tool.c */
void	*v_malloc(size_t size);
void	cleanup(char **paths, char *new_prog);
char	*get_env_value(char *key, t_exec exec);

#endif
