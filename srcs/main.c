#include "../includes/lem_in.h"

int		clean_quit(t_btree **graph, const int ret)
{
	if (ret == 1)
		ft_printf("{red}ERROR{reset}\n");
	btree_deep_del(graph);
	return (ret);
}

void	print_btree(void *data)
{
	t_room	*room;

	room = (t_room*)data;
	ft_printf("NAME : %s || X : %3i || Y : %3i || STATUS : %i\n",
			room->name, room->x, room->y, room->status);
}

int		main(int argc, char **argv)
{
	t_btree		*graph;
	t_parser	*data;

	(void)argv;
	if (argc == 1)
	{
		graph = NULL;
		if (!(data = init_parser()))
			return (FAIL);
		if (!(ft_read_stdin(&graph, data)))
			return (clean_quit(&graph, 1));
		btree_apply_infix_lr(graph, print_btree);
		clean_quit(&graph, 0);
	}
	else
		ft_printf("{red}[-] ERROR : wrong number of arguments{reset}\n");
	return (0);
}
