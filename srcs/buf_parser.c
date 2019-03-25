#include "../includes/lem_in.h"

static int	ft_strcpos(const char c, const char *str, const char limit)
{
	int i;

	i = 0;
	// ft_printf("STR = %s\n", str);
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

/*
**	Parse the chunk of data, registering all informations.
**	In the first step (data->steps == 0) we considering the rooms themselves.
**	In the second step (data->steps == 1) we connecting the rooms between them.
*/

int		ft_buf_parser(const char *buf, t_parser *data, t_btree **graph)
{
	int		i;

	i = 0;
	// ft_printf("%s\n", buf);
	while (buf[i])
	{
		// ft_printf("%i & %i & |%s|\n", data->steps, i, &buf[i]);
		if (ft_strncmp(&buf[i], COMMENTARY, 1) == 0)
			ft_register_com(&buf[i], &i, data);
		else if (data->steps == 0)
		{
			if (!(ft_strcpos(' ', &buf[i], '\n')))
			{
				// ft_printf("phase 2 |%s|%i\n", &buf[i], ft_strcpos(' ', buf, '\n'));
				data->steps = 1;
				if (data->start == NULL || data->end == NULL)
					return (FAIL);
			}
			else
				if (!(ft_register_room(buf, &i, data, graph)))
					return (FAIL);
			data->status = LAMBDA;
		}
		else
		{
			if (ft_strcpos(' ', &buf[i], '\n')
					|| !ft_strcpos('-', &buf[i], '\n'))
				return (FAIL);
			// if (!(ft_register_path(buf, &i, graph)))
			// 	return (FAIL);
			data->status = LAMBDA;
		}
		i++;
	}
	return (1);
}
