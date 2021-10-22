/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tyuan <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/22 17:00:34 by tyuan             #+#    #+#             */
/*   Updated: 2021/10/22 17:00:57 by tyuan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <sys/wait.h>
# include <sys/errno.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <curses.h>
# include <term.h>
# include <dirent.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>

# define NQ	'0'
# define SINGLE_QUOTED '1'
# define DOUBLE_QUOTED '2'
# define QUOTATION_MARK '3'

# define WORD 0
# define GREAT 1
# define DGREAT 2
# define LESS 3
# define UNQUOTED_SPACE 4

typedef struct s_token
{
	int		type;
	char	*word;
	char	*quoted;
}	t_token;

typedef struct s_list
{
	t_token			*content;
	struct s_list	*next;
}	t_list;

typedef struct s_cml
{
	char	*line;
	t_list	*lst_token;
	t_list	*lst_redi;
	char	**argv;
}	t_cml;

/* parse.c */
t_cml	*parse(char *line);
t_cml	*parse_pipe(char *line);
void	set_token(t_cml *cml);
void	parse_redirection(t_list **lst, char **l, char **quoted);
void	quote_removal(t_token *tok);

/* parse2.c */
void	variable_expansion(t_token *tok);
int		locate_vars_to_expand(t_token *tok, int *start, int *end);
int		expand(char **tabs, char **tab_q);
char	*quoted_bit_reset(char *line, char c, int *type);
void	var_space_splitting(t_list	*lst_token);
void	set_argv(t_cml *cml);

/* tool_parse.c */
void	remove_substr(char **line, int sub_start, int sub_end);
char	*combine_strings(char **tabs);
void	str_idx_split(char *l, int *start, int *end, char **tabs);
int		num_of_vars(t_token *tok);
int		amount_of_cmls(char **cml_tab);

/* tool_parse2.c */
int		if_unquoted_space(t_list *lst);

/* tool_token.c */
t_token	*new_token(int type, char *nword, char *nquo);
void	chang_token_value(t_token *tok, int type, char *nword, char *nquo);
char	*be_not_quoted(char *w);
char	*set_quoted_bits(char *line);
int		typeof_redi(char *line);

/* tool_parse_split.c */
char	**jump_quotes_ft_split(char const *s, char *quoted, char c);
void	*ft_memset(void *b, int c, size_t len);
int		docp(char **tabs, char const *s, int *ct);
int		sizec(char const *s, char c);

/* tool_libft_str.c */
size_t	ft_strlen(const char *s);
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	*ft_strdup(const char *s1);
size_t	ft_strlcat(char *restrict dst, const char *restrict src,
			size_t dstsize);
char	*strjoin(char const *s1, char const *s2);

/* tool_libft_lst.c */
t_list	*ft_lstnew(void *content);
void	ft_lstiter(t_list *lst, void (*f)(t_token *));
void	ft_lstadd_back(t_list **alst, t_list *new);
t_list	*ft_lstlast(t_list *lst);
int		ft_lstsize(t_list *lst);

#endif
