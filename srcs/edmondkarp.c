/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   edmondkarp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jergauth <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/19 14:09:02 by jergauth          #+#    #+#             */
/*   Updated: 2019/04/23 16:58:41 by cmoulini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

static void	display_moves(t_parser *data)
{
	int	line_count;

	line_count = 0;
	ft_printf("\n");
	while (data->end->ant < data->ants)
	{
		push_colony(data);
		ft_putchar('\n');
		line_count++;
	}
	if (data->line_count == 1)
		ft_printf("{green}[+] Solved in %i %s !{reset}\n",
			line_count, (line_count > 1) ? "lines" : "line");
}

/*
**	Edmond Karp's algorithm give us the max flow in a graph.
**	It use the Breadth First Search (also called BFS) to do so.
**	For each iteration, we make a residual graph that is the result of all
**	the previous iteration plus the new one.
*/

int			edmondkarp(t_parser *data)
{
	int	flow_max;
	int	tmp_tours;
	int	tours;

	tours = -1;
	flow_max = 0;
	while (ft_bfs(data) && data->ants > flow_max)
	{
		flow_max++;
		if (!(flow_direction(data)))
			return (FAIL);
		detect_vertex_separator(data);
		set_len_path(data);
		if (!(ft_ants_repartition(data, &tmp_tours)))
			return (FAIL);
		if (tours == -1 || tmp_tours < tours)
		{
			tours = tmp_tours;
			ft_keep_flow(data->start, data);
		}
	}
	if (flow_max == 0)
		return (FAIL);
	display_moves(data);
	return (SUCCESS);
}
