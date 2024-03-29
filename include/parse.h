/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tyuan <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/22 17:00:34 by tyuan             #+#    #+#             */
/*   Updated: 2021/11/18 17:18:39 by jkromer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_H
# define PARSE_H

# define NQ	'0'
# define SINGLE_QUOTED '1'
# define DOUBLE_QUOTED '2'
# define QUOTATION_MARK '3'

# define WORD 0
# define GREAT 1
# define DGREAT 2
# define LESS 3
# define UNQUOTED_SPACE 4
# define HEREDOC 5

/* parse.c */
t_cml		*parse(char *line, t_exec exec);
t_cml		*parse_pipe(char *line);
void		set_token(t_cml *cml);
void		parse_redirection(t_tknlst **lst, char **l, char **quoted);
void		quote_removal(t_token *tok, t_exec *exec);

/* parse2.c */
void		variable_expansion(t_token *tok, t_exec *exec);
int			locate_vars_to_expand(t_token *tok, int *start, int *end);
int			expand(char **tabs, char **tab_q, t_exec exec, int type);
void		var_space_splitting(t_tknlst	*lst_token);
void		set_argv(t_cml *cml);

/* syntax.c */
int			check_syntax(char *line, t_exec exec);
int			unclosed_quot_mrks(char *line, char **p);

/* heredoc.c */
char		*str_variable_expansion(char *line, t_exec exec, int n);
void		str_expand(char **tabs, t_exec exec);
void		heredoc_cprocess(char *fpath, char *delim, int expand, t_exec exec);
int			creat_heredoc(char *delim, int expand, t_exec exec);
char		*check_heredoc(char *operator, char *line, t_exec exec);

/* tool_cml_redi.c */
void		init_cml(t_cml *cmls);
int			amount_of_cmls(char **cml_tab);
int			num_of_vars(t_token *tok);
int			if_unquoted_space_in_redi(t_tknlst *lst);
int			typeof_redi(char *line);

/* tool_heredoc.c */
void		set_heredoc_path(t_cml *cmls);
int			wait_heredoc(char *filepath);
char		*available_heredoc_name(void);

/* token.c */
t_token		*new_token(int type, char *nword, char *nquo);
void		change_token_value(t_token *tok, int type, char *nword, char *nquo);
char		*be_not_quoted(char *w);
char		*set_quoted_bits(char *line);
char		*quoted_bit_reset(char *line, char c, int *type);

/* split.c */
char		**jump_quotes_ft_split(char const *s, char *quoted, char c);
int			docp(char **tabs, char const *s, int *ct);
int			sizec(char const *s, char c);

/* tool_str.c */
char		*sh_substr(char const *s, unsigned int start, size_t len);
char		*sh_strjoin(char const *s1, char const *s2);
int			str_start_with(const char *line, char c);
int			str_end_with(const char *line, char c);
char		*str_quote_removal(char *str);

/* tool_str2.c */
void		remove_substr(char **line, int sub_start, int sub_end);
char		*combine_strings(char **tabs);
void		str_idx_split(char *l, int *start, int *end, char **tabs);
void		remove_substrs(char **l, char **q, int s, int e);

/* tknlst.c */
t_tknlst	*tknlstnew(void *tkn);
void		tknlstiter(t_tknlst *lst, t_exec *op,
				void (*f)(t_token *, t_exec *));
void		tknlstadd_back(t_tknlst **alst, t_tknlst *new);
t_tknlst	*tknlstlast(t_tknlst *lst);
int			tknlstsize(t_tknlst *lst);

#endif
