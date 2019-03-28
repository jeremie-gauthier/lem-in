#include "../includes/lem_in.h"

static int	ft_add_neighbours(t_room *nghbr1, t_room *nghbr2)
{
	t_list	*tmp;

	if (!(tmp = ft_lstnew((void*)nghbr2, sizeof(nghbr2))))
		return (0);
	ft_lstadd(&nghbr1->nghbr, tmp);
	if (!(tmp = ft_lstnew((void*)nghbr1, sizeof(nghbr1))))
		return (0);
	ft_lstadd(&nghbr2->nghbr, tmp);
	return (1);
}

int			ft_register_path(const char *buf, int *i, t_btree **graph)
{
	t_room	*nghbr1;
	t_room	*nghbr2;
	int		(*cmpf)(const void *, const void *);

	cmpf = &ft_btreeccmp_hyphen;
	if (!(nghbr1 = btree_search_data(*graph, (void*)&buf[*i], cmpf)))
		return (0);
	*i += (ft_strcspn(&buf[*i], "-") + 1);
	if (buf[*i] == '-')
		return (0);
	cmpf = &ft_btreeccmp_newline;
	if (!(nghbr2 = btree_search_data(*graph, (void*)&buf[*i], cmpf)))
		return (0);
	*i += (ft_strcspn(&buf[*i], "\n"));
	// ft_printf("nghb1 => %s\nnghb2 => %s\n", nghbr1->name, nghbr2->name);
	if (!(ft_add_neighbours(nghbr1, nghbr2)))
		return (0);
	return (1);
}
