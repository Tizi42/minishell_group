/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkromer <jkromer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/11 19:21:55 by jkromer           #+#    #+#             */
/*   Updated: 2021/11/15 12:47:16 by jkromer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

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
	pid_t	*pids;
	int		pipe_fds[2][2];
	int		nb_ps;
	int		nb_pipe;
	int		saved_stdin;
	int		saved_stdout;
}			t_exec;

struct s_sig
{
	pid_t	pid;
	int		*status;
};

#endif
