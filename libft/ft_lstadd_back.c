#include "libft.h"

void	ft_lstadd_back(t_list **head, t_list *new)
{
	t_list	*current;

	if (head == NULL || *head == NULL)
		*head = new;
	else
	{
		current = *head;
		while (current->next)
			current = current->next;
		current->next = new;
	}
}