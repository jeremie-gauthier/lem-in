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
