#include "../includes/lem_in.h"

static char	*ft_strcdup(const char *buf, int *i, const char limit)
{

}

int			ft_register_room(const char *buf, int *i, t_parser *data, t_btree **graph)
{
	char	*name;

	name = NULL;
	while (buf[*i] && buf[*i] != '\n')
	{
		if (name == NULL)
		{
			if (!(name = ft_strcdup(&buf[*i], *i, ' ')))
				return (FAIL);
			if (buf[*i] == ' ')
				return (clean_quit(&name));
			btree_insert_data(graph, (void*)name, ft_btreecmp);
			if (!(register_coord_x(&buf[*i], i, *graph, name)))
				return (clean_quit(&name));
			if (buf[*i] == ' ')
				return (clean_quit(&name));
			if (!(register_coord_y(&buf[*i], i, *graph, name)))
				return (clean_quit(&name));
		}
		(*i)++;
	}
	return (SUCCESS);
}
