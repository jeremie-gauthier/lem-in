#include "../includes/lem_in.h"

int		ft_register_com(const char *buf, int *i, t_parser *data)
{
	int	j;

	j = 0;
	if (ft_strncasecmp(buf, START_COM, 8) == IDENTICAL)
		data->status = START;
	else if (ft_strncasecmp(buf, END_COM, 6) == IDENTICAL)
		data->status = END;
	while (buf[j] && buf[j] != '\n')
		j++;
	*i += j;
	return (1);
}
