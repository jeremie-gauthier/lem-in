/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_btreecmp.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jergauth <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/19 14:09:09 by jergauth          #+#    #+#             */
/*   Updated: 2019/04/19 14:09:09 by jergauth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

int	ft_btreecmp(const void *struct1, const void *struct2)
{
	const t_room	*room1;
	const t_room	*room2;
	const char		*name1;
	const char		*name2;

	room1 = struct1;
	room2 = struct2;
	name1 = room1->name;
	name2 = room2->name;
	while (*name1 && *name2 && *name1 == *name2)
	{
		name1++;
		name2++;
	}
	return ((int)*name1 - (int)*name2);
}

int	ft_btreeccmp_hyphen(const void *struc, const void *str)
{
	const t_room	*room;
	const char		*name1;
	const char		*name2;

	room = struc;
	name1 = room->name;
	name2 = str;
	while (*name1 && *name2 && *name1 == *name2
				&& *name2 != '-' && *(name2 + 1) != '-')
	{
		name1++;
		name2++;
	}
	return ((int)*name1 - (int)*name2);
}

int	ft_btreeccmp_newline(const void *struc, const void *str)
{
	const t_room	*room;
	const char		*name1;
	const char		*name2;

	room = struc;
	name1 = room->name;
	name2 = str;
	while (*name1 && *name2 && *name1 == *name2
				&& *name2 != '\n' && *(name2 + 1) != '\n')
	{
		name1++;
		name2++;
	}
	return ((int)*name1 - (int)*name2);
}
