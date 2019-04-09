#include "libft.h"

void	ft_lstpop(t_list **head)
{
	t_list	*tmp;

	if (*head)
	{
		tmp = *head;
		*head = (*head)->next;
		tmp->content = NULL;
		tmp->content_size = 0;
		tmp->next = NULL;
		ft_memdel((void*)tmp);
	}
}
