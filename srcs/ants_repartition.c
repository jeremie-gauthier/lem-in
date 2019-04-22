#include "../includes/lem_in.h"

static int		ft_get_nb_flows(t_parser *data)
{
	t_list	*ngbr;
	t_edge	*edge;
	int		ret;

	ret = 0;
	ngbr = data->start->nghbr;
	while (ngbr)
	{
		edge = ngbr->content;
		if (edge->tmp_flow == 1)
			ret++;
		ngbr = ngbr->next;
	}
	return (ret);
}

static int	valid(t_room *room, t_parser *data)
{
	t_list	*ngbr;
	t_edge	*edge;

	if (room == data->end)
		return (1);
	if (room != data->end)
	{
		ngbr = room->nghbr;
		while (ngbr)
		{
			edge = ngbr->content;
			// edge->flow = edge->tmp_flow;
			// edge->room->capacity = edge->room->tmp_capacity;
			if (edge->tmp_flow == 1)
				if (valid(edge->room, data))
					return (1);
			ngbr = ngbr->next;
		}
	}
	return (0);
}

static t_room	**init_roomtab(t_parser *data, int len)
{
	t_room	**new;
	t_list	*ngbr;
	t_edge	*edge;
	int		i;

	if (!(new = (t_room**)malloc(sizeof(*new) * len + 1)))
		return (NULL);
	i = 0;
	ngbr = data->start->nghbr;
	while (ngbr)
	{
		edge = ngbr->content;
		if (edge->tmp_flow == 1)
		{
			new[i] = edge->room;
			i++;
		}
		ngbr = ngbr->next;
	}
	new[i] = NULL;
	return (new);
}

static void	ft_sort_roomtab(t_room **tab, int len)
{
	t_room *tmp;
	int		i;
	int		j;

	i = 0;
	while (i < len - 1)
	{
		j = i + 1;
		while (j < len)
		{
			// ft_printf("TEST %i %i %s\n", len, i, tab[j]->name);
			if (tab[i]->len_path > tab[j]->len_path)
			{
				tmp = tab[i];
				tab[i] = tab[j];
				tab[j] = tmp;
			}
			j++;
		}
		i++;
	}
}

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
			{
				tab[i]->tmp_capacity++;
				ant_not_set = false;
				tmp_ants--;
			}
			else if (ft_cmproom_capa(tab[i], tab[i + 1]) == 1)
			{
				tab[i]->tmp_capacity++;
				ant_not_set = false;
				tmp_ants--;
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

static void ft_print_neigh(t_parser *data)
{
	t_list *ngbr;
	t_edge *edge;

	ngbr = data->start->nghbr;
	while (ngbr)
	{
		edge = ngbr->content;
		if (edge->tmp_flow)
			ft_printf("%s - %i\n", edge->room->name, edge->room->tmp_capacity);
		ngbr = ngbr->next;
	}
	ft_printf("\n\n");
}

static void	reset_previous_data(t_room **tab, int len)
{
	int	i;

	i = 0;
	while (i < len)
	{
		tab[i]->tmp_capacity = 0;
		i++;
	}
}

int			ft_ants_repartition(t_parser *data, int *max_tours)
{
	t_room	**tab;
	int		len;

	len = ft_get_nb_flows(data);
	if (!(tab = init_roomtab(data, len)))
		return (FAIL);
	reset_previous_data(tab, len);
	ft_sort_roomtab(tab, len);
	ft_balance_ants(data, tab, len);
	get_max_tours(tab, len, max_tours);
	// ft_print_neigh(data);
	ft_memdel((void*)&tab);
	return (SUCCESS);
}
