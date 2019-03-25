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

int			ft_register_x(const char *buf, int *i, t_btree *graph, const char *name)
{
	long	x;
	int		diff;
	int		len;
	t_btree	*node;
	t_room	*room;

	if (*buf == '\0' || name == NULL)
		return (FAIL);
	diff = ft_strcspn(buf, " ");
	x = ft_atol_base(buf, 10);
	len = ft_intlen(x);
	if (diff - len != 0)
		return (FAIL);
	if (x < -2147483648 || x > 2147483647)
		return (FAIL);
	if (!(node = btree_search_data(graph, (void*)name, ft_btreecmp)))
		return (FAIL);
	room = node->data;
	room->x = x;
	*i += len;
	return (SUCCESS);
}

int			ft_register_y(const char *buf, int *i, t_btree *graph, const char *name)
{
	long	y;
	int		diff;
	int		len;
	t_btree	*node;
	t_room	*room;

	if (*buf == '\0' || name == NULL)
		return (FAIL);
	diff = ft_strcspn(buf, "\n");
	y = ft_atol_base(buf, 10);
	len = ft_intlen(y);
	if (diff - len != 0)
		return (FAIL);
	if (y < -2147483648 || y > 2147483647)
		return (FAIL);
	if (!(node = btree_search_data(graph, (void*)name, ft_btreecmp)))
		return (FAIL);
	room = node->data;
	room->y = y;
	*i += len;
	return (SUCCESS);
}
