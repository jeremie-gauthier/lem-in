#include "../includes/lem_in.h"

int	edmondkarp(t_parser *data)
{
	int	i;
	
	i = 0;
	while (ft_bfs(data) && data->ants > i)
	{
		if (!(flow_direction(data)))
			return (FAIL);
		i++;
	}
	while (data->end->ant < data->ants)
	{
		push_colony(data);
		ft_putchar('\n');
	}
	return (SUCCESS);
}
