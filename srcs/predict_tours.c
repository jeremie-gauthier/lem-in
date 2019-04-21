#include "../includes/lem_in.h"

static int	get_path_len(t_room *room, t_parser *data)
{
	t_room	*current;
	int		len;

	current = room;
	len = 1;
	while (current != data->end)
	{
		current = get_next_room(current);
		len++;
	}
	return (len);
}

static void	evaluate_tours(t_room *room, int path_len, int *ret)
{
	int	tours;

	if (room->tmp_capacity > 0)
	{
		tours = path_len + room->tmp_capacity - 1;
		if (tours > *ret)
			*ret = tours;
	}
}

int			ft_predict_tours(t_parser *data)
{
	t_list	*ngbr;
	t_edge	*edge;
	int		path_len;
	int		ret;

	ngbr = data->start->nghbr;
	path_len = 0; // peut etre a suppr
	ret = 0;
	while (ngbr)
	{
		edge = ngbr->content;
		if (edge->tmp_flow == 1)
		{
			path_len = get_path_len(edge->room, data);
			// ft_printf("Room : %s HAS %i\n", edge->room->name, edge->room->tmp_capacity);
			evaluate_tours(edge->room, path_len, &ret);
		}
		ngbr = ngbr->next;
	}
	return (ret);
}

static void	evaluate_tours_bis(t_room *room, int path_len, int *ret)
{
	int	tours;

	if (room->tmp_capacity > 0)
	{
		tours = path_len + room->tmp_capacity - 1;
		*ret = tours;
	}
}

static void	optimal_balance_capacity(t_parser *data, int *tmp_ants, int max_tours)
{
	t_list	*ngbr;
	t_edge	*edge;
	int		path_len; // peut etre a suppr
	int		tours;

	ngbr = data->start->nghbr;
	while (ngbr)
	{
		edge = ngbr->content;
		if (edge->tmp_flow == 1)
		{
			path_len = get_path_len(edge->room, data);
			// ft_printf("Room : %s HAS %i\n", edge->room->name, edge->room->tmp_capacity);
			evaluate_tours_bis(edge->room, path_len, &tours);
			// ft_printf("Tour %i vs max %i\n", tours, max_tours);
			if (tours < max_tours)
			{
				// ft_printf("ENTERING %s capa is %i and len is %i\n", edge->room->name, edge->room->tmp_capacity, path_len);
				while (tours < max_tours && *tmp_ants > 0)
				{
					edge->room->tmp_capacity++;
					tours++;
					(*tmp_ants)--;
				}
			}
		}
		ngbr = ngbr->next;
	}
}

void		ft_redistribute_flux(t_parser *data, int tmp_ants,
				t_room *best_path)
{
	t_list	*ngbr;
	t_edge	*edge;
	int		path_len;
	int		max_tours;

	ngbr = data->start->nghbr;
	path_len = 0; // peut etre a suppr
	max_tours = 0;
	while (ngbr)
	{
		edge = ngbr->content;
		if (edge->tmp_flow == 1)
		{
			path_len = get_path_len(edge->room, data);
			// ft_printf("Room : %s HAS %i\n", edge->room->name, edge->room->tmp_capacity);
			evaluate_tours(edge->room, path_len, &max_tours);
		}
		ngbr = ngbr->next;
	}
	optimal_balance_capacity(data, &tmp_ants, max_tours);
	if (tmp_ants > 0)
		best_path->tmp_capacity += tmp_ants;
}
