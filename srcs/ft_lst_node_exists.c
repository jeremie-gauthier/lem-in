#include "lem_in.h"

t_bool	ft_lst_node_exists(t_list *head, t_room *node)
{
	t_room	*tmp;

	if (head == NULL || node == NULL)
		return (false);
	while (head)
	{
		tmp = head->content;
		if (tmp == node)
			return (true);
		head = head->next;
	}
	return (false);
}
