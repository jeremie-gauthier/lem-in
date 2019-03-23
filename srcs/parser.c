#include "../includes/lem_in.h"

static int	clean_quit(t_parser **data, int ret)
{
	ft_memdel((void*)data);
	return (ret);
}

int			read_stdin(t_btree **graph)
{
	char		buf[BUF_SIZE + 1];
	t_parser	*data;
	int			i;

	if (!(data = init_parser()))
		return (0);
	while ((data->ret = read(0, buf, BUF_SIZE)) > 0)
	{
		buf[data->ret] = '\0';
		i = 0;
		if (data->ants == -1)
			if (!(register_ants(&buf[i], &i, data)))
				return (clean_quit(&data, 0));
		(void)graph;
	}
	ft_printf("ants = %i\n", data->ants);
	return (clean_quit(&data, 1));
}
