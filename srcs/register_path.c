#include "../includes/lem_in.h"

/*
**	Creates a connection between two rooms by adding each room
**	in the neighbours' list of each other.
*/

static int		ft_add_neighbours(t_room *nghbr1, t_room *nghbr2)
{
	t_list	*tmp;

	if (!(tmp = ft_lstnew_addr((void*)nghbr2)))
		return (0);
	ft_lstadd(&nghbr1->nghbr, tmp);
	if (!(tmp = ft_lstnew_addr((void*)nghbr1)))
		return (0);
	ft_lstadd(&nghbr2->nghbr, tmp);
	return (1);
}

static t_room	*ft_parse_room_name(const char *buf, t_btree *graph,
					const t_parser *data, const int pos)
{
	t_room	*ret;
	int		(*cmpf)(const void *, const void *);

	if (pos == LEFT)
		cmpf = &ft_btreeccmp_hyphen;
	else
		cmpf = &ft_btreeccmp_newline;
	if (ft_strncasecmp(buf, START_STR, 5) == IDENTICAL)
		return (data->start);
	if (ft_strncasecmp(buf, END_STR, 3) == IDENTICAL)
		return (data->end);
	if ((ret = btree_search_data(graph, (void*)buf, cmpf)))
		return (ret);
	return (NULL);
}

/*
**	Register the address of the two rooms
**	involving in the creation of the path that links them.
**	Then create the connection between them with `ft_add_neighbours`
*/

int				ft_register_path(const char *buf, int *i, t_btree **graph,
					t_parser *data)
{
	t_room	*nghbr1;
	t_room	*nghbr2;

	if (!(nghbr1 = ft_parse_room_name(&buf[*i], *graph, data, LEFT)))
		return (0);
	*i += (ft_strcspn(&buf[*i], "-") + 1);
	if (buf[*i] == '-')
		return (0);
	if (!(nghbr2 = ft_parse_room_name(&buf[*i], *graph, data, RIGHT)))
		return (0);
	*i += (ft_strcspn(&buf[*i], "\n"));
	if (!(ft_add_neighbours(nghbr1, nghbr2)))
		return (0);
	return (1);
}
