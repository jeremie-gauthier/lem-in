/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jergauth <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/23 16:33:54 by jergauth          #+#    #+#             */
/*   Updated: 2019/04/23 16:33:55 by jergauth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

t_parser	*init_parser(void)
{
	t_parser	*new;

	if (!(new = (t_parser*)malloc(sizeof(*new))))
		return (NULL);
	new->ants = -1;
	new->status = 0;
	new->start_set = 0;
	new->end_set = 0;
	new->steps = 0;
	new->ret = 0;
	new->start = NULL;
	new->end = NULL;
	new->last_line = NULL;
	new->malloced = false;
	new->room_temoin = 0;
	return (new);
}

t_room		*init_room(char *name, const int status)
{
	t_room	*new;

	if (!(new = (t_room*)malloc(sizeof(*new))))
		return (NULL);
	new->name = name;
	new->x = 0;
	new->y = 0;
	new->ant = 0;
	new->nghbr = NULL;
	new->status = status;
	new->ancestor = NULL;
	new->len_path = 0;
	new->room_used = 0;
	new->vertex_used = 0;
	new->tmp_capacity = 0;
	new->capacity = 0;
	return (new);
}

t_edge		*init_edge(t_room *room)
{
	t_edge	*new;

	if (!(new = (t_edge*)malloc(sizeof(*new))))
		return (NULL);
	new->room = room;
	new->tmp_flow = 0;
	new->flow = 0;
	return (new);
}

t_room		**init_roomtab(t_parser *data, int len)
{
	t_room	**new;
	t_list	*ngbr;
	t_edge	*edge;
	int		i;

	if (!(new = (t_room**)malloc(sizeof(*new) * (len + 1))))
		return (NULL);
	i = 0;
	ngbr = data->start->nghbr;
	while (ngbr)
	{
		edge = ngbr->content;
		if (edge->tmp_flow == 1)
		{
			new[i] = edge->room;
			i++;
		}
		ngbr = ngbr->next;
	}
	new[i] = NULL;
	return (new);
}
