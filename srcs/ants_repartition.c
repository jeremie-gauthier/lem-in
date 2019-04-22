#include "../includes/lem_in.h"

static t_room	**init_roomtab(t_parser *data, int flow_max)
{
	t_room	**new;
	t_list	*ngbr;
	t_edge	*edge;
	int		i;

	if (!(new = (t_room**)malloc(sizeof(*new) * flow_max)))
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
	return (new);
}

static void	ft_sort_roomtab(t_room ***tab, int len)
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
			ft_printf("%s\n", (*tab[1])->name);
			if ((*tab[i])->len_path > (*tab[j])->len_path)
			{
				tmp = *tab[i];
				*tab[i] = *tab[j];
				*tab[j] = tmp;
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

	tours_current = current->capacity + 1 + current->len_path - 1;
	tours_next = next->capacity + 1 + next->len_path - 1;
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
				tab[i]->capacity++;
				ant_not_set = false;
				tmp_ants--;
			}
			else if (ft_cmproom_capa(tab[i], tab[i + 1]) == 1)
			{
				tab[i]->capacity++;
				ant_not_set = false;
				tmp_ants--;
			}
			i++;
		}
	}
}

int			ft_ants_repartition(t_parser *data, int flow_max)
{
	t_room	**tab;

	if (!(tab = init_roomtab(data, flow_max)))
		return (FAIL);
	int j = 0;
	while (j < flow_max)
	{
		ft_printf("avant %s -> %i\n", tab[j]->name, tab[j]->len_path);
		j++;
	}
	ft_sort_roomtab(&tab, flow_max);
	int i = 0;
	while (i < flow_max)
	{
		ft_printf("apres %s -> %i\n", tab[i]->name, tab[i]->len_path);
		i++;
	}
	ft_balance_ants(tab, flow_max);
	ft_memdel((void*)&tab);
	return (SUCCESS);
}
