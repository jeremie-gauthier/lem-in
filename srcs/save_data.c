/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jergauth <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/19 14:11:24 by jergauth          #+#    #+#             */
/*   Updated: 2019/04/19 14:11:25 by jergauth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

int		ft_save_data(const char *buf, t_parser *data, int *i)
{
	int	j;

	j = 0;
	if (!(data->last_line = ft_strdup(buf)))
		return (FAIL);
	while (buf[j])
		j++;
	*i += j;
	return (SUCCESS);
}
