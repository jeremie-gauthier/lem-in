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

// static void ft_print_neigh(t_parser *data)
// {
// 	t_list *ngbr;
// 	t_edge *edge;

// 	ngbr = data->start->nghbr;
// 	while (ngbr)
// 	{
// 		edge = ngbr->content;
// 		if (edge->flow)
// 			ft_printf("%s - %i\n", edge->room->name, edge->room->capacity);
// 		ngbr = ngbr->next;
// 	}
// }

int	edmondkarp(t_parser *data)
{
	int	flow_max;
	int	tmp_tours;
	int	tours;

	tours = -1;
	flow_max = 0;
	while (ft_bfs(data) && data->ants > i)
	{
		if (!(flow_direction(data)))
			return (FAIL);
		detect_vertex_separator(data);
		ft_balance_flow(data);
		tmp_tours = ft_predict_tours(data);
		// ft_printf("prediction => %i\n", tmp_tours);
		if (tours == -1 || tmp_tours < tours)
		{
			tours = tmp_tours;
			ft_keep_flow(&data);
		}
		flow_max++;
	}
	if (flow_max == 0)
		return (FAIL);
	//ft_printf("nb %i\nTOURS PREDICTION => %i\n", i, tours);
	//ft_print_neigh(data);
	while (data->end->ant < data->ants)
	{
		push_colony(data);
	//	ft_printf("end => %i && ants => %i\n", data->end->ant, data->ants);
		ft_putchar('\n');
	}
	return (SUCCESS);
}
