#include "../includes/lem_in.h"

static int		get_len_path(t_room *room, t_parser *data)
{
	t_room	*current;
	int		len;

	current = room;
	len = 1;
	while (current != data->end)
	{
		current = get_next_room(current);
		len++;
	}
	return (len);
}

void	set_len_path(t_parser *data)
{
	t_list	*ngbr;
	t_edge	*edge;

	ngbr = data->start->nghbr;
	while (ngbr)
	{
		edge = ngbr->content;
		if (edge->tmp_flow == 1)
			edge->room->len_path = get_len_path(edge->room, data);
		ngbr = ngbr->next;
	}
}
