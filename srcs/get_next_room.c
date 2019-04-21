#include "../includes/lem_in.h"

t_room	*get_next_room(t_room *room)
{
	t_list	*ngbr;
	t_edge	*edge;

	ngbr = room->nghbr;
	while (ngbr)
	{
		edge = ngbr->content;
		if (edge->tmp_flow == 1)
			return (edge->room);
		ngbr = ngbr->next;
	}
	return (NULL);
}
