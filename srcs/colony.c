#include "../includes/lem_in.h"

t_bool	valid_origin(t_room *room, t_room *origin)
{
	t_list	*ngbr;
	t_edge	*edge;

	ngbr = origin->nghbr;
	while (ngbr)
	{
		edge = ngbr->content;
		if (edge->room == room && edge->flow == 1)
			return (true);
		ngbr = ngbr->next;
	}
	return (false);
}

t_room	*get_origin(t_room *current, t_list *ngbr)
{
	t_edge	*edge;

	while (ngbr)
	{
		edge = ngbr->content;
		if (valid_origin(current, edge->room))
			return (edge->room);
		ngbr = ngbr->next;
	}
	return (NULL);
}

int		move_ant(t_room *current, t_room *origin, t_parser *data)
{
	while (current != data->start)
	{
		if ((current->ant == 0 || current == data->end) && origin->ant != 0
				&& origin->ant <= data->ants && (origin->room_used != data->room_temoin || origin == data->start))
		{
			if (origin == data->start && current->capacity > 0)
			{
				current->capacity--;
				ft_printf("L%i-%s ", origin->ant, current->name);
				if (current == data->end)
					current->ant++;
				else
					current->ant = origin->ant;
				if (origin == data->start)
					origin->ant++;
				else
					origin->ant = 0;
				current->room_used = data->room_temoin;
			}
			else if (origin != data->start)
			{
				ft_printf("L%i-%s ", origin->ant, current->name);
				if (current == data->end)
					current->ant++;
				else
					current->ant = origin->ant;
				if (origin == data->start)
					origin->ant++;
				else
					origin->ant = 0;
				current->room_used = data->room_temoin;
			}
		}
		current = origin;
		if (current != data->start)
			if (!(origin = get_origin(current, current->nghbr)))
				return (FAIL);
	}
	return (SUCCESS);
}

int		push_colony(t_parser *data)
{
	t_list	*ngbr;
	t_edge	*edge;

	data->room_temoin = ~data->room_temoin;
	ngbr = data->end->nghbr;
	while (ngbr)
	{
		edge = ngbr->content;
		if (valid_origin(data->end, edge->room))
			move_ant(data->end, edge->room, data);
		ngbr = ngbr->next;
	}
	return (1);
}