#include "../includes/lem_in.h"

int	edmondkarp(t_parser *data)
{
	while(ft_bfs(data))
	{
		if (!(flow_direction(data)))
			return(FAIL);
	}
	return(SUCCESS);
}