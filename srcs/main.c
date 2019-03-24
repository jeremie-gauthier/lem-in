#include "../includes/lem_in.h"

int		clean_quit(t_btree **graph, const int ret)
{
	if (ret == 1)
		ft_printf("{red}ERROR{reset}\n");
	btree_del(graph, 1);
	return (ret);
}

int		main(int argc, char **argv)
{
	t_btree	*graph;

	(void)argv;
	if (argc == 1)
	{
		graph = NULL;
		if (!(ft_read_stdin(&graph)))
			return (clean_quit(&graph, 1));
	}
	else
		ft_printf("{red}[-] ERROR : wrong number of arguments{reset}\n");
	return (0);
}
