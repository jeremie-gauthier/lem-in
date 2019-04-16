#include "../includes/lem_in.h"

static t_bool	clean_quit(t_list **queue, t_bool ret)
{
	ft_lstdel(queue, NULL);
	return (ret);
}

static int		ft_bfs_enqueue(t_room *current, t_list **queue, t_list *neighbours, t_parser *data)
{
	t_edge	*edge;
	t_room	*tmp;
	t_list	*neighbour;

	while (neighbours)
	{
		edge = neighbours->content;
		tmp = edge->room;
		if (edge->flow == 0 && !ft_lst_node_exists(*queue, tmp))
		{
			tmp->ancestor = current;
			if (tmp == data->end)
				return (1);
			if (!(neighbour = ft_lstnew_addr((void*)tmp)))
				return (-1);
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
	int		ret;

	if (!(queue = ft_lstnew_addr((void*)data->start)))
		return (false);
	current = queue;
	while (current)
	{
		room = current->content;
		ret = ft_bfs_enqueue(room, &queue, room->nghbr, data);
		if (ret == 1)
			return (clean_quit(&queue, true));
		else if (ret == -1)
			return (clean_quit(&queue, false));
		current = current->next;
	}
	return (clean_quit(&queue, false));
}
