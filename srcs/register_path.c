#include "../includes/lem_in.h"

/*
**	Creates a connection between two rooms by adding each room
**	in the neighbours' list of each other.
*/

static int		ft_add_neighbours(t_room *nghbr1, t_room *nghbr2)
{
	t_list	*tmp;
	t_edge	*edge1;
	t_edge	*edge2;

	if (!(edge2 = init_edge(nghbr2)))
		return (FAIL);
	if (!(tmp = ft_lstnew_addr((void*)edge2)))
	{
		ft_memdel((void*)&edge2);
		return (FAIL);
	}
	ft_lstadd(&nghbr1->nghbr, tmp);
	if (!(edge1 = init_edge(nghbr1)))
	{
		ft_memdel((void*)&edge2);
		return (FAIL);
	}
	if (!(tmp = ft_lstnew_addr((void*)edge1)))
	{
		ft_memdel((void*)&edge2);
		ft_memdel((void*)&edge1);
		return (FAIL);
	}
	ft_lstadd(&nghbr2->nghbr, tmp);
	return (SUCCESS);
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
		return (FAIL);
	*i += (ft_strlimit(&buf[*i], '-') + 1);
	if (buf[*i] == '-')
		return (FAIL);
	if (!(nghbr2 = ft_parse_room_name(&buf[*i], *graph, data, RIGHT)))
		return (FAIL);
	*i += (ft_strlimit(&buf[*i], '\n'));
	if (!(ft_add_neighbours(nghbr1, nghbr2)))
		return (FAIL);
	return (SUCCESS);
}
