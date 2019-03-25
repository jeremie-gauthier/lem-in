#include "../includes/lem_in.h"

static int	clean_quit(char **str, t_room **room)
{
	ft_strdel(str);
	if (room)
		del_room(room);
	return (FAIL);
}

static char	*ft_strcdup(const char *buf, int *i, const char limit)
{
	int		len;
	char	*new;
	int		tmp;

	len = 0;
	tmp = 0;
	if (buf == NULL)
		return (NULL);
	while (buf && buf[len] != limit)
		len++;
	if (!(new = (char*)malloc(sizeof(*new) * len + 1)))
		return (NULL);
	*i += len + 1;
	while (tmp < len)
	{
		new[tmp] = buf[tmp];
		tmp++;
	}
	new[tmp] = '\0';
	return (new);
}

int			ft_register_room(const char *buf, int *i, t_parser *data, t_btree **graph)
{
	(void)data;
	char	*name;
	t_room	*room;

	// ft_printf("buf %s -- %i\n", &buf[*i], *i);
	while (buf[*i] && buf[*i] != '\n')
	{
		if (!(name = ft_strcdup(&buf[*i], i, ' ')))
			return (FAIL);
		if (!(room = init_room(name, data->status)))
			return (clean_quit(&name, NULL));
		if (buf[*i] == ' ')
			return (clean_quit(NULL, &room));
		btree_insert_data(graph, (void*)room, ft_btreecmp);
		if (!(ft_register_x(&buf[*i], i, room)))
			return (clean_quit(NULL, &room));
		if (buf[*i] == ' ')
			return (clean_quit(NULL, &room));
		if (!(ft_register_y(&buf[*i], i, room)))
			return (clean_quit(NULL, &room));
	}
	return (SUCCESS);
}
