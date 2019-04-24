/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   register_room.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmoulini <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/19 13:58:00 by cmoulini          #+#    #+#             */
/*   Updated: 2019/04/19 13:59:00 by cmoulini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

static int	clean_quit(char **str, t_room **room)
{
	ft_strdel(str);
	del_room(room);
	return (FAIL);
}

/*
**	Duplicate the name of a room in a fresh memory string.
**	The name is contained between the first char and the 'limit' char.
**	It also checks for the validity of the room's name ('-' not included)
*/

static char	*ft_strcdup_room(const char *buf, int *i, const char limit,
				t_parser *data)
{
	int		len;
	char	*new;
	int		tmp;

	if (buf == NULL || buf[0] == 'L')
		return (ft_set_err_code_ptr(data, 10));
	len = 0;
	while (buf[len] && buf[len] != limit)
	{
		if (buf[len] == '-')
			return (ft_set_err_code_ptr(data, 10));
		len++;
	}
	if (!(new = (char*)malloc(sizeof(*new) * len + 1)))
		return (ft_set_err_code_ptr(data, 1));
	*i += len + 1;
	tmp = 0;
	while (tmp < len)
	{
		new[tmp] = buf[tmp];
		tmp++;
	}
	new[tmp] = '\0';
	return (new);
}

static int	ft_search_duplicate(const t_room *room, t_btree *graph, t_parser *data)
{
	t_room	*ret;
	int		(*cmpf)(const void *, const void *);

	cmpf = &ft_btreecmp;
	ret = (t_room*)btree_search_data(graph, (void*)room, cmpf);
	if (ret == NULL)
		return (0);
	return (ft_set_err_code(data, 9));
}

static void	ft_register_start_end(t_parser *data, t_room *room)
{
	if (data->status != LAMBDA)
	{
		if (data->status == START)
		{
			data->start = room;
			data->start->ant = 1;
			if (data->color_auto == 1)
				room->color = green;
		}
		else if (data->status == END)
		{
			data->end = room;
			if (data->color_auto == 1)
				room->color = red;
		}
	}
}

/*
**	Register a line that contains the correct informations (name x y).
**	Else, returns ERROR.
*/

int			ft_register_room(const char *buf, int *i, t_parser *data,
				t_btree **graph)
{
	t_room	*room;
	char	*name;
	int		(*cmpf)(const void *, const void *);

	cmpf = &ft_btreecmp;
	if (!(name = ft_strcdup_room(&buf[*i], i, ' ', data)))
		return (FAIL);
	if (!(room = init_room(name, data)))
		return (clean_quit(&name, NULL));
	if (ft_search_duplicate(room, *graph, data))
		return (clean_quit(NULL, &room));
	if (buf[*i] == ' ')
		return (clean_quit(NULL, &room));
	if (!(btree_insert_data(graph, (void*)room, cmpf)))
		return (clean_quit(NULL, &room));
	if (!(ft_register_coord(&buf[*i], i, room, ' ')))
		return (ft_set_err_code(data, 10));
	if (buf[*i] == ' ')
		return (ft_set_err_code(data, 9));
	if (!(ft_register_coord(&buf[*i], i, room, '\n')))
		return (ft_set_err_code(data, 10));
	ft_register_start_end(data, room);
	return (SUCCESS);
}
