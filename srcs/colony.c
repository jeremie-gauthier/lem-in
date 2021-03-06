/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colony.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jergauth <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/19 14:08:58 by jergauth          #+#    #+#             */
/*   Updated: 2019/04/25 15:52:23 by cmoulini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

static void		display_move_msg(t_room *current, t_room *origin,
					t_parser *data)
{
	char	*palet[7];

	palet[red] = RED;
	palet[green] = GREEN;
	palet[yellow] = YELLOW;
	palet[blue] = BLUE;
	palet[magenta] = MAGENTA;
	palet[cyan] = CYAN;
	if (origin == data->start && data->color_auto == 1)
		ft_printf("{green}");
	else if (current == data->end && data->color_auto == 1)
		ft_printf("{red}");
	else if (current->color != -1)
		ft_printf("%s", palet[current->color]);
	ft_printf("L%i-%s ", origin->ant, current->name);
	if ((origin == data->start && data->color_auto == 1)
			|| (current == data->end && data->color_auto == 1)
			|| current->color != -1)
		ft_printf("{reset}");
}

static int		move_ant(t_room *current, t_room *origin, t_parser *data)
{
	if (origin == data->start && current->capacity <= 0)
		return (FAIL);
	else if (origin == data->start && current->capacity > 0)
		current->capacity--;
	display_move_msg(current, origin, data);
	if (current == data->end)
		current->ant++;
	else
		current->ant = origin->ant;
	if (origin == data->start)
		origin->ant++;
	else
		origin->ant = 0;
	current->room_used = data->room_temoin;
	return (SUCCESS);
}

static t_bool	valid_origin(t_room *room, t_room *origin)
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

static int		reverse_depth_search(t_room *current, t_room *origin,
					t_parser *data)
{
	t_list	*ngbr;
	t_edge	*edge;

	if (current == data->start)
		return (1);
	if ((current->ant == 0 || current == data->end) && origin->ant != 0
				&& origin->ant <= data->ants
				&& (origin->room_used != data->room_temoin
				|| origin == data->start))
		move_ant(current, origin, data);
	current = origin;
	ngbr = current->nghbr;
	while (ngbr)
	{
		edge = ngbr->content;
		if (valid_origin(current, edge->room))
		{
			origin = edge->room;
			reverse_depth_search(current, origin, data);
		}
		ngbr = ngbr->next;
	}
	return (0);
}

/*
**	For each neighbour of the starting node, we are running a Depth First Search
**	from the end to the beginning.
**	We are trying every neighbours for each node, attempting to find the parent
**	node until we reach start.
*/

int				push_colony(t_parser *data)
{
	t_list	*ngbr;
	t_edge	*edge;

	data->room_temoin = ~data->room_temoin;
	ngbr = data->end->nghbr;
	while (ngbr)
	{
		edge = ngbr->content;
		if (valid_origin(data->end, edge->room))
			reverse_depth_search(data->end, edge->room, data);
		ngbr = ngbr->next;
	}
	return (1);
}
