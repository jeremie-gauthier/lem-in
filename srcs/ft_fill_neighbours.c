#include "lem_in.h"

// void	ft_lst_push_back(t_list **head, t_room *new)
// {
// 	t_list	*current;

// 	if (head == NULL || *head == NULL)
// 		*head = new;
// 	else
// 	{
// 		current = *head;
// 		while (current->next)
// 			current = current->next;
// 		current->next = new;
// 	}
// }

void	ft_fill_neighbours(t_list **head, t_list *to_add)
{

	if (head && *head && to_add)
	{
		while (to_add)
		{
			if (!(ft_lst_node_exists(*head, to_add->content)))
				ft_lstadd_back(head, to_add);
			to_add = to_add->next;
		}
	}
}