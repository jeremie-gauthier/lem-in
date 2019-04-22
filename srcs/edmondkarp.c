/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   edmondkarp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jergauth <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/19 14:09:02 by jergauth          #+#    #+#             */
/*   Updated: 2019/04/19 14:09:03 by jergauth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

static int	valid(t_room *room, t_parser *data)
{
	t_list	*ngbr;
	t_edge	*edge;

	ft_printf("ROOM -> %s\n", room->name);
	if (room == data->end)
		return (1);
	ngbr = room->nghbr;
	while (ngbr)
	{
		edge = ngbr->content;
		// edge->flow = edge->tmp_flow;
		// edge->room->capacity = edge->room->tmp_capacity;
		if (edge->flow == 1)
			if (valid(edge->room, data))
				return (1);
		ngbr = ngbr->next;
	}
	return (0);
}

static void ft_print_neigh(t_parser *data)
{
	t_list *ngbr;
	t_edge *edge;

	ft_printf("---KEEP DATA---\n");
	ngbr = data->start->nghbr;
	while (ngbr)
	{
		edge = ngbr->content;
		if (edge->flow)
		{
			ft_printf("%s - %i - %i - %i\n", edge->room->name, edge->room->capacity, edge->flow, edge->room->len_path);
			if (ft_strcmp(edge->room->name, "Px_5") == IDENTICAL)
				valid(edge->room, data);
			// 	ft_printf("OK :)\n");
			// else
			// 	ft_printf("KO ! :(\n");
		}
		ngbr = ngbr->next;
	}
	ft_printf("---END---\n");
}

int	edmondkarp(t_parser *data)
{
	int	flow_max;
	int	tmp_tours;
	int	tours;

	tours = -1;
	flow_max = 0;
	while (ft_bfs(data) && data->ants > flow_max)
	{
		flow_max++;
		// ft_printf("FLOW DETECTES => %i\n", flow_max);
		if (!(flow_direction(data)))
			return (FAIL);
		detect_vertex_separator(data);
		// ft_balance_flow(data);
		// tmp_tours = ft_predict_tours(data);
		set_len_path(data);
		if (!(ft_ants_repartition(data, &tmp_tours)))
			return (FAIL);
		// ft_printf("prediction => %i\n", tmp_tours);
		if (tours == -1 || tmp_tours < tours)
		{
			tours = tmp_tours;
			ft_keep_flow(data->start, data);
			// ft_print_neigh(data);
		}
	}
	if (flow_max == 0)
		return (FAIL);
	// ft_printf("nb %i\nTOURS PREDICTION => %i\n", flow_max, tours);
	// ft_print_neigh(data);
	while (data->end->ant < data->ants)
	{
		push_colony(data);
		// ft_print_neigh(data);
		// ft_printf("end => %i && ants => %i\n", data->end->ant, data->ants);
		ft_putchar('\n');

	}
	return (SUCCESS);
}
