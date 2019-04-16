#include "../includes/lem_in.h"

static int	isset_flow_opposite(t_list *neighbours, t_room *current)
{
	t_edge	*edge;
	t_room	*tmp;

	while (neighbours)
	{
		edge = neighbours->content;
		tmp = edge->room;
		if (tmp == current)
		{
			if (edge->flow == 1)
			{
				edge->flow = 0;
				return (1);
			}
		}
		neighbours = neighbours->next;
	}
	return (0);
}

static int	set_flow(t_list *neighbours, t_room *current, t_room *next)
{
	t_edge	*edge;
	t_room	*tmp;

	while (neighbours)
	{
		edge = neighbours->content;
		tmp = edge->room;
		if (tmp == next)
		{
			if (!isset_flow_opposite(next->nghbr, current))
				edge->flow = 1;
			return (SUCCESS);
		}
		neighbours = neighbours->next;
	}
	return (FAIL);
}

int			flow_direction(t_parser *data)
{
	t_room *current;
	t_room *tmp;

	tmp = data->end;
	current = data->end->ancestor;
	while (current != data->start)
	{
		if (!(set_flow(current->nghbr, current, tmp)))
			return (FAIL);
		tmp = current;
		current = current->ancestor;
	}
	if (!(set_flow(current->nghbr, current, tmp)))
		return (FAIL);
	return (SUCCESS);
}
