/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkromer <jkromer@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/16 11:50:52 by jkromer           #+#    #+#             */
/*   Updated: 2021/11/12 17:00:02 by jkromer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <stdlib.h>
# include <unistd.h>

typedef struct s_list	t_list;
struct		s_list
{
	void	*c;
	t_list	*n;
};

void				*ft_memset(void *s, int c, size_t n);
void				ft_bzero(void *s, size_t n);
void				*ft_memcpy(void *dest, const void *src, size_t n);
void				*ft_memccpy(void *dest, const void *src, int c, size_t n);
void				*ft_memmove(void *dest, const void *src, size_t n);
void				*ft_calloc(size_t nmemb, size_t size);
void				*ft_memchr(const void *s, int c, size_t n);
int					ft_memcmp(const void *s1, const void *s2, size_t n);
size_t				ft_strlen(const char *s);
char				*ft_strdup(const char *s);
char				*ft_strndup(const char *s, size_t n);
char				*ft_strcat(char *dst, const char *src);
size_t				ft_strlcat(char *dst, const char *src, size_t size);
size_t				ft_strlcpy(char *dst, const char *src, size_t size);
char				*ft_strchr(const char *s, int c);
char				*ft_strrchr(const char *s, int c);
char				*ft_strnstr(const char *big, const char *little,
						size_t len);
int					ft_strncmp(const char *s1, const char *s2, size_t n);
int					ft_strcmp(const char *s1, const char *s2);
int					ft_atoi(const char *nptr);
int					ft_atoi_base(const char *s, const char *base);
int					ft_isalpha(int c);
int					ft_isdigit(int c);
int					ft_isalnum(int c);
int					ft_isascii(int c);
int					ft_isprint(int c);
int					ft_isspace(int c);
int					ft_tolower(int c);
int					ft_toupper(int c);
char				*ft_substr(char const *s, unsigned int start, size_t len);
char				*ft_strmapi(char const *s,
						char (*f)(unsigned int, char));
char				*ft_strjoin(size_t size, const char **strs,
						const char *sep);
char				*ft_strtrim(char const *str, char const *set);
char				**ft_split(char const *s, const char *sep);
char				*ft_itoa(int n);
char				*ft_itoa_base(int n, const char *base);
void				ft_putstr(const char *s);
void				ft_putchar(char c);
void				ft_putnbr(int n);
void				ft_putchar_fd(char c, int fd);
void				ft_putstr_fd(char *s, int fd);
void				ft_putendl_fd(char *s, int fd);
void				ft_putnbr_fd(int n, int fd);
t_list				*ft_lstnew(void *c);
void				ft_lstadd_front(t_list **alst, t_list *new);
int					ft_lstsize(t_list *lst);
t_list				*ft_lstlast(t_list *lst);
void				ft_lstadd_back(t_list **alst, t_list *new);
void				ft_lstdelete(t_list *lst);
void				ft_lstclear(t_list *lst);
void				ft_lstiter(t_list *lst, void (*f)(void *));
t_list				*ft_lstmap(t_list *lst, void *(*f)(void *));
int					ft_indexof(char c, const char *s);
int					ft_puts(const char *str);
int					ft_starts_with(const char *str, const char *pattern);
int					ft_ends_with(const char *str, const char *pattern);
char				*ft_strcpy(char *dst, const char *src);
char				*ft_strmerge(const char *s1, const char *s2);
int					ft_contains(const char *s, char c);
int					get_n_line(int fd, char **line);
void				clear_gnl(int fd);
int					fill_buffer(int fd, char *buffer, int *n);
int					is_sep(char c, const char *sep);
void				free_split(char **split);
int					count_elems(char **split);
double				rad(double a);
void				swap(int *a, int *b);
unsigned long long	ft_atoul(const char *s);

#endif
