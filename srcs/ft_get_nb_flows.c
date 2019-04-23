/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_nb_flows.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jergauth <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/23 16:33:38 by jergauth          #+#    #+#             */
/*   Updated: 2019/04/23 16:33:39 by jergauth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

int		ft_get_nb_flows(t_parser *data)
{
	t_list	*ngbr;
	t_edge	*edge;
	int		ret;

	ret = 0;
	ngbr = data->start->nghbr;
	while (ngbr)
	{
		edge = ngbr->content;
		if (edge->tmp_flow == 1)
			ret++;
		ngbr = ngbr->next;
	}
	return (ret);
}
