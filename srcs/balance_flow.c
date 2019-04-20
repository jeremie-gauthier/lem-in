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
**	Predict the number of toours necessary to complete the graph
*/

static void		set_tours(int len_path, int ants, int *tours)
{
	int	ret;

	if (ants > 0)
	{
		ret = len_path + ants - 1;
		// ft_printf("ret = len_pat + ants - 1\n%i = %i + %i - 1\n", ret, len_path, ants);
		if (ret > *tours && ret > 0)
			*tours = ret;
	}
}

static t_room	*get_next(t_room *room)
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
		current = get_next(current);
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
					t_room *best_path, int *tours)
{
	t_list	*ngbr;
	t_edge	*edge;
	int		tmp_ants;
	int		relative_cap;
	int		len_path;

	tmp_ants = data->ants;
	ngbr = data->start->nghbr;
	while (ngbr)
	{
		edge = ngbr->content;
		if (edge->tmp_flow == 1)
		{
			if (edge->room->tmp_capacity != 0)
				len_path = 100 / edge->room->tmp_capacity;
			else
				len_path = 0;
			relative_cap = (int)((float)edge->room->tmp_capacity
					/ (float)sum_capacity * 100);
			edge->room->tmp_capacity = (int)((float)relative_cap
					/ (float)100 * data->ants);
			set_tours(len_path, edge->room->tmp_capacity, tours);
			tmp_ants -= edge->room->tmp_capacity;
			// ft_printf("Room -> %s Got -> %i\n", edge->room->name, edge->room->tmp_capacity);
		}
		ngbr = ngbr->next;
	}
	best_path->tmp_capacity += tmp_ants;
	// ft_printf("Room -> %s Got -> %i\n", best_path->name, best_path->tmp_capacity);
}

/*
**	room->capacity will give us the number of ants we must send
**	to the path.
*/

int				ft_balance_flow(t_parser *data, int *tours)
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
	*tours = -1;
	set_relative_capacity(sum_capacity, data, best_path, tours);
	return (SUCCESS);
}
