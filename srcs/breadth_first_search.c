#include "lem_in.h"

static int	ft_bfs_enqueue(t_room *current, t_list **queue, t_list *neighbours, t_parser *data)
{
	t_edge	*edge;
	t_list	*neighbour;
	t_room	*tmp;

	while (neighbours)
	{
		edge = neighbours->content;
		tmp = edge->room;
		// print_list(*queue);
		// ft_printf("ENQUEUE %s\n", edge->room->name);
		if (edge->flow == 0 && !ft_lst_node_exists(*queue, tmp))//&& (*queue)->ancestor == NULL)
		{
			// ft_printf("c : %s | v : %s\n", current->name, tmp->name);
			// if (current != data->start)
			tmp->ancestor = current;
			if (tmp == data->end)
				return (1);
			if (!(neighbour = ft_lstnew_addr((void*)tmp)))
				return (FAIL); // traiter ce cas d'erreur
			ft_lstadd_back(queue, neighbour);
		}
		neighbours = neighbours->next;
	}
	return (0);
}

t_bool		ft_bfs(t_parser *data)
{
	t_list	*queue;
	t_list	*current;
	t_room	*room;

	if (!(queue = ft_lstnew_addr((void*)data->start)))
		return (false);
	current = queue;
	while (current)
	{
		room = current->content;
		// ft_printf("CURRENT %s\n", room->name);
		if (ft_bfs_enqueue(room, &queue, room->nghbr, data) == 1)
			return (true);
		current = current->next;
	}
	ft_lstdel(&queue, NULL);
	return (false);
}
