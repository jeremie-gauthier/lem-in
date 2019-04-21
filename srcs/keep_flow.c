#include "../includes/lem_in.h"

static void	depth_first_search(t_room *room, t_parser **data)
{
	t_list	*ngbr;
	t_edge	*edge;

	if (room != (*data)->end)
	{
		ngbr = room->nghbr;
		while (ngbr)
		{
			edge = ngbr->content;
			edge->flow = edge->tmp_flow;
			if (edge->tmp_flow == 1)
			{
				// edge->flow = edge->tmp_flow;
				depth_first_search(edge->room, data);
			}
			ngbr = ngbr->next;
		}
	}
}

/*
**	Copy the temporary informations as real informations.
**	tmp ar tmp_flow and tmp_capacity
*/

void	ft_keep_flow(t_parser **data)
{
	t_list	*ngbr;
	t_edge	*edge;

	ngbr = (*data)->start->nghbr;
	while (ngbr)
	{
		edge = ngbr->content;
		// ft_printf("EDGE ROOM NAME %s %i %i %i %i\n", edge->room->name, edge->flow, edge->tmp_flow, edge->room->capacity, edge->room->tmp_capacity);
	//	edge->flow = edge->tmp_flow;
	//	edge->room->capacity = edge->room->tmp_capacity;
		// ft_printf("EDGE ROOM NAME %s %i %i %i %i\n", edge->room->name, edge->flow, edge->tmp_flow, edge->room->capacity, edge->room->tmp_capacity);
		if (edge->tmp_flow == 1)
		{
			 edge->flow = edge->tmp_flow;
			 edge->room->capacity = edge->room->tmp_capacity;
			depth_first_search(edge->room, data);
		}
		ngbr = ngbr->next;
	}
}
