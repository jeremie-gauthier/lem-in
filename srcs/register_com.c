/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   register_com.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmoulini <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/19 13:56:34 by cmoulini          #+#    #+#             */
/*   Updated: 2019/04/19 13:56:35 by cmoulini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

static int	memorize_color(const char *buf, t_parser *data)
{
	char	*palet[7];
	int		i;

	palet[0] = "##RED";
	palet[1] = "##GREEN";
	palet[2] = "##YELLOW";
	palet[3] = "##BLUE";
	palet[4] = "##MAGENTA";
	palet[5] = "##CYAN";
	palet[6] = NULL;
	i = 0;
	while (palet[i])
	{
		if (ft_strncasecmp(buf, palet[i], ft_strlen(palet[i])) == IDENTICAL)
		{
			data->color_next_room = i;
			return (SUCCESS);
		}
		i++;
	}
	return (FAIL);
}

int			ft_register_com(const char *buf, int *i, t_parser *data)
{
	int	j;

	j = 0;
	if (ft_strncasecmp(buf, START_COM, 8) == IDENTICAL)
	{
		if (data->start_set == 1)
			return (ft_set_err_code(data, 2));
		data->status = START;
		data->start_set = 1;
	}
	else if (ft_strncasecmp(buf, END_COM, 6) == IDENTICAL)
	{
		if (data->end_set == 1)
			return (ft_set_err_code(data, 3));
		data->status = END;
		data->end_set = 1;
	}
	else
		memorize_color(buf, data);
	while (buf[j] && buf[j] != '\n')
		j++;
	*i += j;
	return (SUCCESS);
}
