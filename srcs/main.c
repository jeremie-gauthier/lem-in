#include "../includes/lem_in.h"

int		clean_quit(t_btree **graph, const int ret)
{
	char	buf[BUF_SIZE + 1];
	int		red;

	while ((red = read(0, buf, BUF_SIZE)))
	{
		buf[red] = '\0';
		ft_printf("%s", buf);
	}
	if (ret == 1 && red == 0)
		ft_printf("\n");
	if (ret == 1)
		ft_printf("{red}ERROR{reset}\n");
	btree_deep_del(graph);
	return (ret);
}

void	print_btree(void *data)
{
	t_room	*room;
	t_list	*tmp;
	t_room	*tmproom;

	room = (t_room*)data;
	tmp = room->nghbr;
	ft_printf("NAME : %s || X : %3i || Y : %3i || STATUS : %i || ",
			room->name, room->x, room->y, room->status);
	ft_printf("VOISINS => ");
	while (tmp)
	{
		tmproom = (t_room*)tmp->content;
		ft_printf("%s ", tmproom->name);
		tmp = tmp->next;
	}
	ft_printf("\n");
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
		// AFFICHAGE DES DONNEES
		// btree_apply_infix_lr(graph, print_btree);
		ft_printf("{green}OK =){reset}\n"); //
		clean_quit(&graph, 0);
	}
	else
		ft_printf("{red}[-] ERROR : wrong number of arguments{reset}\n");
	return (0);
}
