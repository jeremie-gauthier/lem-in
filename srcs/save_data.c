#include "../includes/lem_in.h"

int		ft_save_data(const char *buf, t_parser *data)
{
	if (!(data->last_line = ft_strdup(buf)))
		return (FAIL);
	ft_printf("|%s|\n", data->last_line);
	return (SUCCESS);
}
