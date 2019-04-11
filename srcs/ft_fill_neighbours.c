#include "lem_in.h"

int		ft_fill_neighbours(t_list **head, t_list *to_add)
{
	t_list	*tmp;

	if (!head || !*head || !to_add)
		return (FAIL);
	while (to_add)
	{
		if (!(ft_lst_node_exists(*head, to_add->content)))
		{
			if (!(tmp = ft_lstnew_addr((void*)to_add->content)))
				return (FAIL);
			ft_lstadd_back(head, tmp);
		}
		to_add = to_add->next;
	}
	return (SUCCESS);
}
