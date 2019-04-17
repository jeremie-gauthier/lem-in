#include "../includes/lem_in.h"

/*
**	Reads and register informations from stdin.
**	It reads chunks of BUF_SIZE bytes and clusterizes informations by
**	chunk > line > segment.
*/

int			ft_read_stdin(t_btree **graph, t_parser *data)
{
	char		buf[BUF_SIZE + 1];
	int			i;

	while ((data->ret = read(0, buf, BUF_SIZE)) > 0)
	{
		buf[data->ret] = '\0';
		ft_printf("%s", buf);
		i = 0;
		if (data->ants == -1)
			if (!(ft_register_ants(&buf[i], &i, data)))
				return (FAIL);
		if (!(ft_buf_parser(&buf[i], data, graph)))
			return (FAIL);
	}
	if (data->ret == 0 && *graph == NULL)
		return (FAIL);
	ft_printf("\n");
	return (SUCCESS);
}
