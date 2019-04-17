#include "../includes/lem_in.h"

static int	clean_quit(char **buf, t_parser *data, const int ret)
{
	if (data->malloced == true)
	{
		ft_strdel(buf);
		data->malloced = false;
	}
	return (ret);
}

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

int			ft_buf_parser(char *buf, t_parser *data, t_btree **graph)
{
	char	*tmp;
	int		i;

	tmp = buf;
	if (data->last_line != NULL)
	{
		if (!(tmp = ft_strjoin(data->last_line, tmp)))
			return (clean_quit(NULL, data, FAIL));
		data->malloced = true;
		ft_strdel(&data->last_line);
	}
	i = 0;
	while (tmp[i])
	{
		if (data->ret == BUF_SIZE && !ft_strcpos('\n', &tmp[i], '\0'))
		{
			if (!(ft_save_data(&tmp[i], data, &i)))
				return (clean_quit(&tmp, data, FAIL));
		}
		else
		{
			if (tmp[i] == '#')
				ft_register_com(&tmp[i], &i, data);
			else
			{
				if (!(ft_room_parser(tmp, data, graph, &i)))
					return (clean_quit(&tmp, data, FAIL));
			}
			i++;
		}
	}
	return (clean_quit(&tmp, data, SUCCESS));
}
