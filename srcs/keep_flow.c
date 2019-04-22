#include "../includes/lem_in.h"

/*
**	Copy the temporary informations as real informations.
**	tmp ar tmp_flow and tmp_capacity
*/

void	ft_keep_flow(t_room *room, t_parser *data)
{
	t_list	*ngbr;
	t_edge	*edge;

	if (room != data->end)
	{
		ngbr = room->nghbr;
		while (ngbr)
		{
			edge = ngbr->content;
			edge->flow = edge->tmp_flow;
			edge->room->capacity = edge->room->tmp_capacity;
			if (edge->tmp_flow == 1)
				ft_keep_flow(edge->room, data);
			ngbr = ngbr->next;
		}
	}
}
