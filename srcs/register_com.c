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

int		ft_register_com(const char *buf, int *i, t_parser *data)
{
	int	j;

	j = 0;
	if (ft_strncasecmp(buf, START_COM, 8) == IDENTICAL)
	{
		if (data->start_set == 1)
			return (FAIL);
		data->status = START;
		data->start_set = 1;
	}
	else if (ft_strncasecmp(buf, END_COM, 6) == IDENTICAL)
	{
		if (data->end_set == 1)
			return (FAIL);
		data->status = END;
		data->end_set = 1;
	}
	while (buf[j] && buf[j] != '\n')
		j++;
	*i += j;
	return (SUCCESS);
}
