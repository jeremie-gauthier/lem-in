#include "../includes/lem_in.h"

static int	clean_quit(char **str, t_room **room)
{
	ft_strdel(str);
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

static int	ft_search_duplicate(const t_room *room, t_btree *graph)
{
	t_room	*ret;
	
	ret = (t_room*)btree_search_data(graph, (void*)room, ft_btreecmp);
	if (ret == NULL)
		return (0);
	return (1);
}

static void	ft_register_start_end(t_parser *data, t_room *room)
{
	if (data->status != LAMBDA)
	{
		if (data->status == START)
			data->start = room;
		else if (data->status == END)
			data->end = room;
	}
}

int			ft_register_room(const char *buf, int *i, t_parser *data, t_btree **graph)
{
	char	*name;
	t_room	*room;

	if (buf[*i] == 'L')
		return (FAIL);
	if (!(name = ft_strcdup(&buf[*i], i, ' ')))
		return (FAIL);
	if (!(room = init_room(name, data->status)))
		return (clean_quit(&name, NULL));
	if (ft_search_duplicate(room, *graph))
		return (clean_quit(NULL, &room));
	if (buf[*i] == ' ')
		return (clean_quit(NULL, &room));
	if (!(btree_insert_data(graph, (void*)room, ft_btreecmp)))
		return (clean_quit(NULL, &room));
	if (!(ft_register_x(&buf[*i], i, room)))
		return (FAIL);
	if (buf[*i] == ' ')
		return (FAIL);
	if (!(ft_register_y(&buf[*i], i, room)))
		return (FAIL);
	ft_register_start_end(data, room);
	return (SUCCESS);
}
