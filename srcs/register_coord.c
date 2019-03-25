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

int			ft_register_x(const char *buf, int *i, t_room *room)
{
	long	x;
	int		diff;
	int		len;

	if (*buf == '\0' || room == NULL)
		return (FAIL);
	diff = ft_strcspn(buf, " ");
	x = ft_atol_base(buf, 10);
	len = ft_intlen(x);
	if (diff - len != 0)
		return (FAIL);
	if (x < -2147483648 || x > 2147483647)
		return (FAIL);
	room->x = x;
	*i += len + 1;
	return (SUCCESS);
}

int			ft_register_y(const char *buf, int *i, t_room *room)
{
	long	y;
	int		diff;
	int		len;

	if (*buf == '\0' || room == NULL)
		return (FAIL);
	diff = ft_strcspn(buf, "\n");
	y = ft_atol_base(buf, 10);
	len = ft_intlen(y);
	if (diff - len != 0)
		return (FAIL);
	if (y < -2147483648 || y > 2147483647)
		return (FAIL);
	room->y = y;
	*i += len;
	return (SUCCESS);
}
