#include "lem_in.h"

void	print_list(t_list *head)
{
	t_room	*tmp;
	int		i;

	i = 0;
	while (head)
	{
		tmp = head->content;
		ft_printf("%i => %s\n", i, tmp->name);
		i++;
		head = head->next;
	}
}

static t_bool	ft_path_exists(t_parser *data)
{
	t_list	*neighbours;
	t_list	*current;
	t_room	*room;

	if (!(neighbours = ft_lstnew_addr((void*)data->start)))
		return (false);
	current = neighbours;
	while (current)
	{
		room = current->content;
		if (ft_lst_node_exists(room->nghbr, data->end))
			return (true);
		ft_fill_neighbours(&neighbours, room->nghbr);
		current = current->next;
	}
	return (false);
}

t_bool			ft_check_validity(t_parser *data)
{
	if (ft_path_exists(data) == false)
		return (false);
	return (true);
}