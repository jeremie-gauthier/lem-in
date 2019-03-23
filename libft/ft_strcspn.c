/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcspn.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jergauth <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/21 14:22:04 by jergauth          #+#    #+#             */
/*   Updated: 2019/03/21 14:22:05 by jergauth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strcspn(const char *s, const char *reject)
{
	size_t	len;

	len = 0;
	if (s && reject)
	{
		while (*s && !ft_strchr(reject, *s))
		{
			len++;
			s++;
		}
	}
	return (len);
}
