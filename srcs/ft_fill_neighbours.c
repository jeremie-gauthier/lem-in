/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fill_neighbours.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jergauth <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/19 14:09:14 by jergauth          #+#    #+#             */
/*   Updated: 2019/04/19 14:09:14 by jergauth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

/*
**	Equivalent to enqueue
*/

int		ft_fill_neighbours(t_list **head, t_list *to_add)
{
	t_list	*tmp;
	t_edge	*edge;

	if (!head || !*head || !to_add)
		return (FAIL);
	while (to_add)
	{
		if (!(ft_lst_edge_exists(*head, to_add->content)))
		{
			edge = to_add->content;
			if (!(tmp = ft_lstnew_addr((void*)edge->room)))
				return (FAIL);
			ft_lstadd_back(head, tmp);
		}
		to_add = to_add->next;
	}
	return (SUCCESS);
}
