#include "../includes/lem_in.h"

static int	clean_quit(t_parser **data, int ret)
{
	ft_memdel((void*)data);
	return (ret);
}

/*
**	Reads and register informations from stdin.
**	It reads chunks of BUF_SIZE bytes and clusterizes informations by
**	chunk > line > segment.
*/

int			ft_read_stdin(t_btree **graph)
{
	char		buf[BUF_SIZE + 1];
	t_parser	*data;
	int			i;

	if (!(data = init_parser()))
		return (FAIL);
	while ((data->ret = read(0, buf, BUF_SIZE)) > 0)
	{
		buf[data->ret] = '\0';
		i = 0;
		if (data->ants == -1)
			if (!(ft_register_ants(&buf[i], &i, data)))
				return (clean_quit(&data, FAIL));
		if (!(ft_buf_parser(&buf[i], data, graph)))
			return (clean_quit(&data, FAIL));
	}
	ft_printf("ants = %i\n", data->ants);
	return (clean_quit(&data, SUCCESS));
}
