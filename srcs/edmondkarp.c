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

static void	display_moves(t_parser *data)
{
	while (data->end->ant < data->ants)
	{
		push_colony(data);
		ft_putchar('\n');
	}
}

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
