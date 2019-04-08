#include "../includes/lem_in.h"

static int	ft_strcpos(const char c, const char *str, const char limit)
{
	int i;

	i = 0;
	while (str && str[i])
	{
		if (str[i] == limit)
			return (0);
		if (c == str[i])
			return (i);
		i++;
	}
	return (0);
}

static int	ft_room_parser(const char *buf, t_parser *data, t_btree **graph, int *i)
{
	if (data->steps == 0)
	{
		if (!(ft_strcpos(' ', &buf[*i], '\n')))
		{
			data->steps = 1;
			if (data->start == NULL || data->end == NULL)
				return (FAIL);
		}
		else
			if (!(ft_register_room(buf, i, data, graph)))
				return (FAIL);
		data->status = LAMBDA;
	}
	if (data->steps == 1)
	{
		if (ft_strcpos(' ', &buf[*i], '\n')
				|| !ft_strcpos('-', &buf[*i], '\n'))
			return (FAIL);
		if (!(ft_register_path(buf, i, graph, data)))
			return (FAIL);
	}
	return (SUCCESS);
}

/*
**	Parse the chunk of data, registering all informations.
**	In the first step (data->steps == 0) we considering the rooms themselves.
**	In the second step (data->steps == 1) we connecting the rooms between them.
*/

int			ft_buf_parser(const char *buf, t_parser *data, t_btree **graph)
{
	int		i;

	i = 0;
	if (data->last_line != NULL)
		if (!(ft_restore_data(buf, data, &i)))
			return (FAIL);
	// i++;
	ft_printf(">>%s|&%i\n", &buf[i], i);
	while (buf[i])
	{
		if (data->ret == BUF_SIZE && !ft_strcpos('\n', &buf[i], '\0'))
		{
			if (!(ft_save_data(&buf[i], data, &i)))
				return (FAIL);
		}
		else
		{
			if (ft_strncmp(&buf[i], COMMENTARY, 1) == IDENTICAL)
				ft_register_com(&buf[i], &i, data);
			else
			{
				if (!(ft_room_parser(buf, data, graph, &i)))
					return (FAIL);
			}
			i++;
		}
	}
	return (1);
}
