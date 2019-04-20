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

int	edmondkarp(t_parser *data)
{
	int	i;
	int	tours;
	int	cmp_tours;

	i = 0;
	cmp_tours = -1;
	while (ft_bfs(data) && data->ants > i)
	{
		if (!(flow_direction(data)))
			return (FAIL);
		detect_vertex_separator(data);
		ft_balance_flow(data, &tours);
		if (tours != -1 && (tours < cmp_tours || cmp_tours == -1))
		{
			//copie des tmp_flow en flow
			// ft_printf("cmp_tours = %i && tours %i\n", cmp_tours, tours);
			ft_keep_flow(data);
			cmp_tours = tours;
		}
		i++;
	}
	if (i == 0)
		return (FAIL);
	// ft_printf("FINAL = %i\n", cmp_tours);
	// ft_printf("FLOW MAX = %i\n", i);
	while (data->end->ant < data->ants)
	{
		push_colony(data);
		// ft_printf("end => %i && ants => %i\n", data->end->ant, data->ants);
		ft_putchar('\n');
	}
	return (SUCCESS);
}
