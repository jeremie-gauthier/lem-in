/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_err_code.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmoulini <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/25 15:58:13 by cmoulini          #+#    #+#             */
/*   Updated: 2019/04/25 15:58:14 by cmoulini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

int		ft_set_err_code(t_parser *data, int code)
{
	data->err_code = code;
	return (FAIL);
}

void	*ft_set_err_code_ptr(t_parser *data, int code)
{
	data->err_code = code;
	return (NULL);
}
