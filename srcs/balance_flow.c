/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   balance_flow.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jergauth <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/19 14:08:42 by jergauth          #+#    #+#             */
/*   Updated: 2019/04/19 14:08:44 by jergauth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

static t_room	*get_next(t_room *room)
{
	t_list	*ngbr;
	t_edge	*edge;

	ngbr = room->nghbr;
	while (ngbr)
	{
		edge = ngbr->content;
		if (edge->flow == 1)
			return (edge->room);
		ngbr = ngbr->next;
	}
	return (NULL);
}

static void		set_capacity(t_room *room, t_parser *data)
{
	t_room			*current;
	unsigned int	len;

	current = room;
	len = 1;
	while (current != data->end)
	{
		current = get_next(current);
		len++;
	}
	room->capacity = (int)((float)1 / (float)len * 100);
	// ft_printf("Room -> %s Capa -> %i\n", room->name, room->capacity);
}

static void		set_relative_capacity(int sum_capacity, t_parser *data,
					t_room *best_path)
{
	t_list	*ngbr;
	t_edge	*edge;
	int		tmp_ants;
	int		relative_cap;

	tmp_ants = data->ants;
	ngbr = data->start->nghbr;
	while (ngbr)
	{
		edge = ngbr->content;
		if (edge->flow == 1)
		{
			relative_cap = (int)((float)edge->room->capacity
					/ (float)sum_capacity * 100);
			edge->room->capacity = (int)((float)relative_cap
					/ (float)100 * data->ants);
			tmp_ants -= edge->room->capacity;
			// ft_printf("Room -> %s Got -> %i\n", edge->room->name, edge->room->capacity);
		}
		ngbr = ngbr->next;
	}
	best_path->capacity += tmp_ants;
	// ft_printf("Room -> %s Got -> %i\n", best_path->name, best_path->capacity);
}

int				ft_balance_flow(t_parser *data)
{
	t_list	*ngbr;
	t_room	*best_path;
	t_edge	*edge;
	int		sum_capacity;
	int		tmp_best_capa;

	ngbr = data->start->nghbr;
	sum_capacity = 0;
	tmp_best_capa = 0;
	while (ngbr)
	{
		edge = ngbr->content;
		if (edge->flow == 1)
		{
			set_capacity(edge->room, data);
			if (edge->room->capacity > tmp_best_capa)
			{
				tmp_best_capa = edge->room->capacity;
				best_path = edge->room;
			}
			sum_capacity += edge->room->capacity;
		}
		ngbr = ngbr->next;
	}
	set_relative_capacity(sum_capacity, data, best_path);
	return (SUCCESS);
}
