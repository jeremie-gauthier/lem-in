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

	i = 0;
	while (ft_bfs(data) && data->ants > i)
	{
		if (!(flow_direction(data)))
			return (FAIL);
		i++;
	}
	if (i == 0)
		return (FAIL);
	detect_vertex_separator(data);
	ft_balance_flow(data);
	while (data->end->ant < data->ants)
	{
		push_colony(data);
		ft_putchar('\n');
	}
	return (SUCCESS);
}
