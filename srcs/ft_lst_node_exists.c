#include "lem_in.h"

t_bool	ft_lst_edge_exists(t_list *head, t_room *node)
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

t_bool	ft_lst_node_exists(t_list *head, t_room *node)
{
	t_room	*tmp;

	if (head == NULL || node == NULL)
		return (false);
	// ft_printf("EXISTS %s\n", node->name);
	while (head)
	{
		tmp = head->content;
		if (tmp == node)
			return (true);
		head = head->next;
	}
	return (false);
}
