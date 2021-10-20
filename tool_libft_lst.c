#include "minishell.h"

t_list	*ft_lstnew(void *content)
{
	t_list *new;

	if (!(new = malloc(sizeof(t_list))))
		return (NULL);
	new->content = content;
	new->next = NULL;
	return (new);
}

void	ft_lstiter(t_list *lst, void (*f)(t_token *))
{
	while (lst)
	{
		(*f)(lst->content);
		lst = lst->next;
	}
}

void	ft_lstadd_back(t_list **alst, t_list *new)
{
	if (*alst == NULL)
	{
		*alst = new;
		return ;
	}
	while (alst && (*alst)->next)
		alst = &((*alst)->next);
	(*alst)->next = new;
}