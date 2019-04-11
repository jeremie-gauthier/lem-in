#include "lem_in.h"

t_bool	ft_lst_node_exists(t_list *head, t_room *node)
{
	t_edge	*edge;

	if (head == NULL || node == NULL)
		return (false);
	while (head)
	{
		edge = head->content;
		if (edge->room == node)
			return (true);
		head = head->next;
	}
	return (false);
}
