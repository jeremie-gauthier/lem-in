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

int		clean_quit(t_btree **graph, t_parser **data, const int ret)
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
		ft_printf("{red}ERROR{reset}\n");
	}
	ft_memdel((void*)data);
	btree_deep_del(graph);
	return (ret);
}

int		main(int argc, char **argv)
{
	t_btree		*graph;
	t_parser	*data;

	if (argc >= 1)
	{
		graph = NULL;
		if (!(data = init_parser()))
		{
			ft_printf("{red}[-] ERROR : Failed to malloc {bold}struct s_parser{reset}{red} in main.\n");
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
		ft_printf("{red}[-] ERROR : wrong number of arguments{reset}\n");
	return (0);
}
