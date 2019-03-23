/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   btree_insert_data.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jergauth <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/21 14:24:22 by jergauth          #+#    #+#             */
/*   Updated: 2019/03/21 14:24:23 by jergauth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
**	Implementation of AVL Trees insertion
*/

static void	insert_right(t_btree **root, void *x, int (*cmpf)(void *, void *))
{
	if (cmpf(x, (*root)->right->data) >= 0)
		btree_rotate_left(root);
	else
	{
		btree_rotate_right(&(*root)->right);
		btree_rotate_left(root);
	}
}

static void	insert_left(t_btree **root, void *x, int (*cmpf)(void *, void *))
{
	if (cmpf(x, (*root)->left->data) < 0)
		btree_rotate_right(root);
	else
	{
		btree_rotate_left(&(*root)->left);
		btree_rotate_right(root);
	}
}

void		btree_insert_data(t_btree **root, void *x,
				int (*cmpf)(void *, void *))
{
	if (*root == NULL)
		*root = btree_create_node(x);
	else
	{
		if (cmpf(x, (*root)->data) >= 0)
		{
			btree_insert_data(&(*root)->right, x, cmpf);
			if (btree_balance_factor(*root) == -2)
				insert_right(root, x, cmpf);
		}
		else
		{
			if (cmpf(x, (*root)->data) < 0)
			{
				btree_insert_data(&(*root)->left, x, cmpf);
				if (btree_balance_factor(*root) == 2)
					insert_left(root, x, cmpf);
			}
		}
		(*root)->height = btree_height(*root);
	}
}
