/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tyuan <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/22 17:00:34 by tyuan             #+#    #+#             */
/*   Updated: 2021/10/27 15:41:59 by jkromer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_H
# define PARSE_H

# include "libft.h"

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
}			t_token;

typedef struct s_tknlst
{
	t_token			*tkn;
	struct s_tknlst	*n;
}					t_tknlst;

typedef struct s_cml
{
	char		*line;
	t_tknlst	*lst_token;
	t_tknlst	*lst_redi;
	char		**argv;
}				t_cml;

/* parse.c */
t_cml		*parse(char *line);
t_cml		*parse_pipe(char *line);
void		set_token(t_cml *cml);
void		parse_redirection(t_tknlst **lst, char **l, char **quoted);
void		quote_removal(t_token *tok);

/* parse2.c */
void		variable_expansion(t_token *tok);
int			locate_vars_to_expand(t_token *tok, int *start, int *end);
int			expand(char **tabs, char **tab_q);
void		var_space_splitting(t_tknlst *lst_token);
void		set_argv(t_cml *cml);

/* tool_parse.c */
void		remove_substr(char **line, int sub_start, int sub_end);
char		*combine_strings(char **tabs);
void		str_idx_split(char *l, int *start, int *end, char **tabs);
int			num_of_vars(t_token *tok);
int			amount_of_cmls(char **cml_tab);

/* tool_parse2.c */
int			if_unquoted_space(t_tknlst *lst);
char		*quoted_bit_reset(char *line, char c, int *type);

/* tool_token.c */
t_token		*new_token(int type, char *nword, char *nquo);
void		chang_token_value(t_token *tok, int type, char *nword, char *nquo);
char		*be_not_quoted(char *w);
char		*set_quoted_bits(char *line);
int			typeof_redi(char *line);

/* tool_parse_split.c */
char		**jump_quotes_ft_split(char const *s, char *quoted, char c);
int			docp(char **tabs, char const *s, int *ct);
int			sizec(char const *s, char c);

/* tool_libft_lst.c */
t_tknlst	*ft_tknlstnew(void *tkn);
void		ft_tknlstiter(t_tknlst *lst, void (*f)(t_token *));
void		ft_tknlstadd_back(t_tknlst **alst, t_tknlst *new);
t_tknlst	*ft_tknlstlast(t_tknlst *lst);
int			ft_tknlstsize(t_tknlst *lst);

#endif
