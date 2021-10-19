#ifndef MINISHELL_H
# define MINISHELL_H

#include <unistd.h>
#include <sys/wait.h>
#include <sys/errno.h>
#include <curses.h>
#include <term.h>
#include <dirent.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>

#define	NQ	'0'
#define SINGLE_QUOTED '1'
#define DOUBLE_QUOTED '2'
#define QUOTATION_MARK '3'

#define WORD 0
#define GREAT 1
#define DGREAT 2
#define LESS 3
#define UNQUOTED_SPACE 4

typedef struct  s_token
{
    int     type;
    char    *word;
    char	*quoted;
}   t_token;

typedef struct  s_cml
{
    char    *line;
    t_list  *lst_token;
    t_list  *lst_redi;
    char    **argv;
}   t_cml;

#endif