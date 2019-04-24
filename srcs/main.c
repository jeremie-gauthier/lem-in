/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jergauth <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/19 14:09:35 by jergauth          #+#    #+#             */
/*   Updated: 2019/04/23 16:58:58 by cmoulini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

static void	err_verbose(t_parser *data)
{
	char	*err_msg[20];

	err_msg[0] = "Failed to malloc";
	err_msg[1] = "Two starting rooms have been found";
	err_msg[2] = "Two ending rooms have been found";
	err_msg[3] = "No ant have been registered";
	err_msg[4] = "The number of ants composing the graph cannot be negative";
	err_msg[5] = "The number of ants is not of int type";
	err_msg[6] = "There is no starting room";
	err_msg[7] = "There is no ending room";
	err_msg[8] = "Try to register a room that already exists";
	err_msg[9] = "Wrong data format";
	err_msg[10] = "Coordinates are not well formated";
	err_msg[11] = "Trying to link an unknown room";
	err_msg[12] = "Superposition error";
	err_msg[13] = "No path found from start to end";
	err_msg[14] = "Wrong room name";
	err_msg[15] = "A connection already exists";
	if (data->err_code >= 1 && data->err_code <= 16)
		ft_printf("{red}[-] ERROR: {bold}%s.{reset}\n", err_msg[data->err_code - 1]);
	else
		ft_printf("{red}ERROR{reset}\n");
}

static int	clean_quit(t_btree **graph, t_parser **data, const int ret)
{
	char	buf[BUF_SIZE + 1];
	int		red;

	if (ret == 1)
	{
		while ((red = read(0, buf, BUF_SIZE)))
		{
			buf[red] = '\0';
			ft_printf("%s", buf);
		}
		if ((*data)->verbose == 1)
			err_verbose(*data);
		else
			ft_printf("{red}ERROR{reset}\n");
	}
	ft_memdel((void*)data);
	btree_deep_del(graph);
	return (ret);
}

int			main(int argc, char **argv)
{
	t_btree		*graph;
	t_parser	*data;

	if (argc >= 1)
	{
		graph = NULL;
		if (!(data = init_parser()))
		{
			ft_printf("{red}[-] ERROR: Failed to malloc {bold}struct s_parser{reset}{red} in main.\n");
			return (1);
		}
		if (argc > 1)
			if (!(ft_parse_args(argv + 1, data)))
				return (clean_quit(NULL, &data, 2));
		if (!(ft_read_stdin(&graph, data)))
			return (clean_quit(&graph, &data, 1));
		if (!(edmondkarp(data)))
			return (clean_quit(&graph, &data, 1));
		clean_quit(&graph, &data, 0);
	}
	else
		ft_printf("{red}[-] ERROR: wrong number of arguments{reset}\n");
	return (0);
}
