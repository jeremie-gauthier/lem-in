/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory_del.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jergauth <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/23 16:33:28 by jergauth          #+#    #+#             */
/*   Updated: 2019/04/23 16:33:29 by jergauth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

void		del_room(t_room **room)
{
	t_list	*current;
	t_list	*tmp;

	ft_strdel(&(*room)->name);
	current = (*room)->nghbr;
	while (current)
	{
		tmp = current->next;
		ft_memdel((void*)current);
		current = tmp;
	}
	ft_lstdel(&(*room)->nghbr, NULL);
	ft_memdel((void*)room);
}

void		btree_deep_del(t_btree **root)
{
	if (root && *root)
	{
		if ((*root)->left)
			btree_deep_del(&(*root)->left);
		if ((*root)->right)
			btree_deep_del(&(*root)->right);
		del_room((t_room**)&(*root)->data);
		ft_memdel((void*)root);
	}
}

void		reset_previous_data(t_room **tab, int len)
{
	int	i;

	i = 0;
	while (i < len)
	{
		tab[i]->tmp_capacity = 0;
		i++;
	}
}
