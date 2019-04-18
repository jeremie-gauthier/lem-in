#include "../includes/lem_in.h"

static int	ft_intlen(long nb)
{
	int	len;

	len = 1;
	len += ((nb < 0) ? 1 : 0);
	while (nb /= 10)
		len++;
	return (len);
}

int		ft_register_ants(const char *buf, int *i, t_parser *data)
{
	long	ants;
	int		diff;
	int		len;

	if (*buf == '\0')
		return (0);
	diff = ft_strlimit(buf, '\n');
	ants = ft_atol_base(buf, 10);
	if (ants <= 0)
		return (FAIL);
	len = ft_intlen(ants);
	if (diff - len != 0)
		return (FAIL);
	if (ants < -2147483648 || ants > 2147483647)
		return (FAIL);
	data->ants = ants;
	*i += len + 1;
	return (SUCCESS);
}
