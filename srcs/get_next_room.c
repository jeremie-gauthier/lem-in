/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_room.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jergauth <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/23 16:35:17 by jergauth          #+#    #+#             */
/*   Updated: 2019/04/23 16:35:18 by jergauth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
