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

int			ft_ants_repartition(t_parser *data, int flow_max)
{
	t_room	**tab;
	
	if (!(tab = init_roomtab(data, flow_max)))
		return (FAIL);
	
	ft_memdel((void*)&tab);
	return (SUCCESS);
}
