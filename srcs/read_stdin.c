/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_stdin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmoulini <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/19 13:56:03 by cmoulini          #+#    #+#             */
/*   Updated: 2019/04/19 13:56:10 by cmoulini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
		if (ft_str_is_ascii(buf))
			ft_printf("%s", buf);
		i = 0;
		while (buf[i] == '#')
		{
			if (!(ft_register_com(&buf[i], &i, data)))
				return (FAIL);
			i++;
		}
		if (data->ants == -1)
			if (!(ft_register_ants(&buf[i], &i, data)))
				return (FAIL);
		if (!(ft_buf_parser(&buf[i], data, graph)))
			return (FAIL);
	}
	if ((data->ret == 0 && *graph == NULL) || data->start == NULL
			|| data->end == NULL)
		return (ft_set_err_code(data, 8));
	return (SUCCESS);
}
