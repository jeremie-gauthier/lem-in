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

/*
**	Capacity here is the 'speed score' of the path.
*/

static void		set_capacity(t_room *room, t_parser *data, int *sum_capacity)
{
	t_room			*current;
	unsigned int	len;

	current = room;
	len = 1;
	while (current != data->end)
	{
		current = get_next_room(current);
		len++;
	}
	room->tmp_capacity = (int)((float)1 / (float)len * 100);
	*sum_capacity += room->tmp_capacity;
	// ft_printf("Room -> %s Capa -> %i\n", room->name, room->tmp_capacity);
}

/*
**	Comparing the 'speed score' between them as shown before,
**	we now attribute the number of ants each path should carry.
*/

static void		set_relative_capacity(int sum_capacity, t_parser *data,
					t_room *best_path)
{
	t_list	*ngbr;
	t_edge	*edge;
	float	relative_cap;
	float	tmp_cap;
	int		tmp_ants;

	tmp_ants = data->ants;
	ngbr = data->start->nghbr;
	while (ngbr)
	{
		edge = ngbr->content;
		if (edge->tmp_flow == 1)
		{
			relative_cap = ((float)edge->room->tmp_capacity
					/ (float)sum_capacity * 100);
			tmp_cap = ((float)relative_cap / (float)100 * data->ants);
			// if (tmp_cap - (int)tmp_cap > 0.5)
			// 	edge->room->tmp_capacity = tmp_cap + 1;
			// else
			if (tmp_cap > 0)
				edge->room->tmp_capacity = tmp_cap - 1;
			else
				edge->room->tmp_capacity = tmp_cap;
			tmp_ants -= edge->room->tmp_capacity;
			// ft_printf("Room -> %s Got -> %i\n", edge->room->name, edge->room->tmp_capacity);
		}
		ngbr = ngbr->next;
	}
	// ft_printf("FOURMIS RESTANTES = %i\n", tmp_ants);
	if (tmp_ants > 0)
		ft_redistribute_flux(data, tmp_ants, best_path);
}

/*
**	room->capacity will give us the number of ants we must send
**	to the path.
*/

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
		if (edge->tmp_flow == 1)
		{
			set_capacity(edge->room, data, &sum_capacity);
			if (edge->room->tmp_capacity > tmp_best_capa)
			{
				tmp_best_capa = edge->room->tmp_capacity;
				best_path = edge->room;
			}
		}
		ngbr = ngbr->next;
	}
	set_relative_capacity(sum_capacity, data, best_path);
	return (SUCCESS);
}
