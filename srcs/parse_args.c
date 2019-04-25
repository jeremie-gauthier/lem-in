/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmoulini <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/25 15:55:20 by cmoulini          #+#    #+#             */
/*   Updated: 2019/04/25 15:57:07 by cmoulini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

static void	display_usage(void)
{
	ft_printf("Usage: ./lem-in [OPTION]...\n\
	-c\tSet Start and End room in green and red.\n\
	-l\tCount lines of the solution.\n\
	-v\tGive more informations on error messages.\n\n\
	Additional commands have been added, you can set a color to a room.\n\
	Available colors are : red, green, yellow, blue, magenta, cyan\n\
	e.g. ##yellow\n");
}

int			ft_parse_args(char **argv, t_parser *data)
{
	while (*argv)
	{
		if (ft_strcmp(*argv, AUTO_COLOR) == IDENTICAL)
			data->color_auto = 1;
		else if (ft_strcmp(*argv, LINE_COUNT) == IDENTICAL)
			data->line_count = 1;
		else if (ft_strcmp(*argv, VERBOSE) == IDENTICAL)
			data->verbose = 1;
		else if (ft_strcmp(*argv, "LANGOUSTE") == IDENTICAL)
			system("sensible-browser https://www.youtube.com/watch?v=KdKCGyUls2Y");
		else
		{
			display_usage();
			return (FAIL);
		}
		argv++;
	}
	return (SUCCESS);
}
