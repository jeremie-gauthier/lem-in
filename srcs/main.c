/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jergauth <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/19 14:09:35 by jergauth          #+#    #+#             */
/*   Updated: 2019/04/19 14:09:36 by jergauth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

int		clean_quit(t_btree **graph, t_parser **data, const int ret)
{
	char	buf[BUF_SIZE + 1];
	int		red;
	t_bool	read_smtg;

	read_smtg = false;
	while ((red = read(0, buf, BUF_SIZE)))
	{
		buf[red] = '\0';
		ft_printf("%s", buf);
		read_smtg = true;
	}
	if (ret == 1 && red == 0 && read_smtg == true)
		ft_printf("\n");
	if (ret == 1)
		ft_printf("{red}ERROR{reset}\n");
	ft_memdel((void*)data);
	btree_deep_del(graph);
	return (ret);
}

void	print_btree(void *data)
{
	t_room	*room;
	t_list	*tmp;
	t_room	*tmproom;
	t_edge	*edge;

	room = (t_room*)data;
	tmp = room->nghbr;
	ft_printf("NAME : %s || STATUS : %i || ANCESTOR : %s || CAPA = %i || ",
			room->name, room->status,
			(room->ancestor == NULL) ? NULL : room->ancestor->name),
			room->capacity;
	ft_printf("VOISINS => ");
	while (tmp)
	{
		edge = (t_edge*)tmp->content;
		tmproom = (t_room*)edge->room;
		ft_printf("%s:%i ", tmproom->name, edge->flow);
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
			return (clean_quit(&graph, &data, 1));
		if (!(edmondkarp(data)))
			return (clean_quit(&graph, &data, 1));
		// btree_apply_infix_lr(graph, print_btree);
		// ft_printf("{green}OK =){reset}\n"); //
		clean_quit(&graph, &data, 0);
	}
	else
		ft_printf("{red}[-] ERROR : wrong number of arguments{reset}\n");
	return (0);
}
