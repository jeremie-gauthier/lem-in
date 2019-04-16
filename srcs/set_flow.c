#include "../includes/lem_in.h"

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
			edge->flow = 1;
			(void)current;
			// collision_flow(edge, current, next);
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
