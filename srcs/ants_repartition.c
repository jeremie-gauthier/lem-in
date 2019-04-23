/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ants_repartition.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jergauth <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/23 16:32:29 by jergauth          #+#    #+#             */
/*   Updated: 2019/04/23 16:32:30 by jergauth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

static int	ft_cmproom_capa(t_room *current, t_room *next)
{
	int	tours_current;
	int	tours_next;

	tours_current = current->tmp_capacity + 1 + current->len_path - 1;
	tours_next = next->tmp_capacity + 1 + next->len_path - 1;
	if (tours_next <= tours_current)
		return (0);
	return (1);
}

static void	ft_set_vars(t_room *room, int *tmp_ants, t_bool *ant_not_set)
{
	room->tmp_capacity++;
	*ant_not_set = false;
	(*tmp_ants)--;
}

static void	ft_balance_ants(t_parser *data, t_room **tab, int len)
{
	t_bool	ant_not_set;
	int		tmp_ants;
	int		i;

	tmp_ants = data->ants;
	while (tmp_ants > 0)
	{
		i = 0;
		ant_not_set = true;
		while (ant_not_set == true)
		{
			if (i == len - 1)
				ft_set_vars(tab[i], &tmp_ants, &ant_not_set);
			else
			{
				if (ft_cmproom_capa(tab[i], tab[i + 1]) == 1)
					ft_set_vars(tab[i], &tmp_ants, &ant_not_set);
			}
			i++;
		}
	}
}

static void	get_max_tours(t_room **tab, int len, int *max_tours)
{
	int	i;
	int	tmp_tours;

	*max_tours = tab[0]->tmp_capacity + tab[0]->len_path - 1;
	if (len > 1)
	{
		i = 1;
		while (i < len)
		{
			tmp_tours = tab[i]->tmp_capacity + tab[i]->len_path - 1;
			if (tmp_tours > *max_tours)
				*max_tours = tmp_tours;
			i++;
		}
	}
}

int			ft_ants_repartition(t_parser *data, int *max_tours)
{
	t_room	**tab;
	int		len;

	len = ft_get_nb_flows(data);
	if (len == 0)
		return (SUCCESS);
	if (!(tab = init_roomtab(data, len)))
		return (FAIL);
	reset_previous_data(tab, len);
	ft_sort_roomtab(tab, len);
	ft_balance_ants(data, tab, len);
	get_max_tours(tab, len, max_tours);
	ft_memdel((void*)&tab);
	return (SUCCESS);
}
