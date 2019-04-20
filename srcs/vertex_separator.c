/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vertex_separator.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jergauth <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/19 14:09:55 by jergauth          #+#    #+#             */
/*   Updated: 2019/04/19 14:09:56 by jergauth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

int		depth_first_search(t_room *room, t_parser *data)
{
	t_list	*ngbr;
	t_edge	*edge;

	if (room == data->end)
		return (SUCCESS);
	if (room->vertex_used == 1)
		return (FAIL);
	ngbr = room->nghbr;
	while (ngbr)
	{
		edge = ngbr->content;
		if (edge->tmp_flow == 1)
		{
			room->vertex_used = 1;
			if (!(depth_first_search(edge->room, data)))
			{
				room->vertex_used = 0;
				edge->tmp_flow = 0;
				return (FAIL);
			}
		}
		ngbr = ngbr->next;
	}
	return (SUCCESS);
}

int		detect_vertex_separator(t_parser *data)
{
	t_list	*ngbr;
	t_edge	*edge;

	ngbr = data->start->nghbr;
	while (ngbr)
	{
		edge = ngbr->content;
		if (edge->flow == 1)
		{
			if (!(depth_first_search(edge->room, data)))
				edge->tmp_flow = 0;
		}
		ngbr = ngbr->next;
	}
	return (SUCCESS);
}
