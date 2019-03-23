/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   btree_search_data.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jergauth <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/21 14:24:48 by jergauth          #+#    #+#             */
/*   Updated: 2019/03/21 14:24:49 by jergauth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*btree_search_data(t_btree *root, void *data_ref,
			int (*cmpf)(void *, void *))
{
	t_btree	*ret;

	ret = NULL;
	if (root && data_ref && cmpf)
	{
		if (root->left)
			ret = btree_search_data(root->left, data_ref, cmpf);
		if (cmpf(data_ref, root->data) == 1)
			return (root);
		if (root->right)
			ret = btree_search_data(root->right, data_ref, cmpf);
	}
	return (ret);
}
