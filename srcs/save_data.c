#include "../includes/lem_in.h"

int		ft_save_data(const char *buf, t_parser *data, int *i)
{
	int	j;

	j = 0;
	if (!(data->last_line = ft_strdup(buf)))
		return (FAIL);
	while (buf[j])
		j++;
	*i += j;
	ft_printf("|%s|\n", data->last_line);
	return (SUCCESS);
}
