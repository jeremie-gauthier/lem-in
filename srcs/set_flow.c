/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_flow.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jergauth <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/19 14:09:49 by jergauth          #+#    #+#             */
/*   Updated: 2019/04/19 14:09:51 by jergauth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
			if (edge->tmp_flow == 1)
			{
				edge->tmp_flow = 0;
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
				edge->tmp_flow = 1;
			return (SUCCESS);
		}
		neighbours = neighbours->next;
	}
	return (FAIL);
}

/*
**	This function attempt to set the new flow for the residual graph.
*/

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
