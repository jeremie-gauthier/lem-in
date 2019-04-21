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
	int	tmp_tours;
	int	tours;

	tours = -1;
	i = 0;
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
		i++;
	}
	if (i == 0)
		return (FAIL);
	// ft_printf("nb %i\nTOURS PREDICTION => %i\n", i, tours);
	while (data->end->ant < data->ants)
	{
		push_colony(data);
		// ft_printf("end => %i && ants => %i\n", data->end->ant, data->ants);
		ft_putchar('\n');
	}
	return (SUCCESS);
}
