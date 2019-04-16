#include "../includes/lem_in.h"

int	edmondkarp(t_parser *data)
{
	int	i;
	
	// ft_printf("ANTS => %i\n", data->ants);
	i = 0;
	while (ft_bfs(data) && data->ants > i)
	{
		if (!(flow_direction(data)))
			return (FAIL);
		i++;
	}
	return (SUCCESS);
}