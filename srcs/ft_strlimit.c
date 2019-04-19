/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlimit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jergauth <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/19 14:09:31 by jergauth          #+#    #+#             */
/*   Updated: 2019/04/19 14:09:32 by jergauth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

int		ft_strlimit(const char *str, const char limit)
{
	int i;

	i = 0;
	while (str && str[i] && str[i] != limit)
		i++;
	return (i);
}
