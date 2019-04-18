#include "../includes/lem_in.h"

static t_bool	numerical_coord(const char *buf, const char limit)
{
	while (*buf && *buf != limit)
	{
		if (*buf < '0' || *buf > '9')
			return (false);
		buf++;
	}
	return (true);
}

static int		ft_intlen(long nb)
{
	int	len;

	len = 1;
	len += ((nb < 0) ? 1 : 0);
	while (nb /= 10)
		len++;
	return (len);
}

int				ft_register_coord(const char *buf, int *i, t_room *room,
					const char limit)
{
	long	coord;
	int		diff;
	int		len;

	if (*buf == '\0' || room == NULL || !numerical_coord(buf, limit))
		return (FAIL);
	diff = ft_strlimit(buf, limit);
	coord = ft_atol_base(buf, 10);
	len = ft_intlen(coord);
	if (diff - len != 0)
		return (FAIL);
	if (coord < -2147483648 || coord > 2147483647)
		return (FAIL);
	if (limit == ' ')
	{
		room->x = coord;
		*i += len + 1;
	}
	else
	{
		room->y = coord;
		*i += len;
	}
	return (SUCCESS);
}
