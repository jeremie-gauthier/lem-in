#include "../includes/lem_in.h"

int		clean_quit(t_btree **graph, const int ret)
{
	if (ret == 1)
		ft_printf("{red}ERROR{reset}\n");
	btree_deep_del(graph);
	return (ret);
}

static void		print_btree(void *data)
{
	t_room	*room;

	room = (t_room*)data;
	ft_printf("NAME : %s || X : %3i || Y : %3i\n", room->name, room->x, room->y);
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
		btree_apply_infix_lr(graph, print_btree);
		clean_quit(&graph, 0);
	}
	else
		ft_printf("{red}[-] ERROR : wrong number of arguments{reset}\n");
	return (0);
}
