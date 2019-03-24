#include "../includes/lem_in.h"

static int	clean_quit(char **str)
{
	ft_strdel(str);
	return (FAIL);
}

static char	*ft_strcdup(const char *buf, int *i, const char limit)
{
	int		len;
	char	*new;
	int		tmp;

	len = 0;
	tmp = 0;
	if (buf == NULL)
		return (NULL);
	while (buf && buf[len] != limit)
		len++;
	if (!(new = (char*)malloc(sizeof(*new) * len + 1)))
		return (NULL);
	*i += len + 1;
	while (tmp < len)
	{
		new[tmp] = buf[tmp];
		tmp++;
	}
	new[tmp] = '\0';
	return (new);
}

int			ft_register_room(const char *buf, int *i, t_parser *data, t_btree **graph)
{
	while (buf[*i] && buf[*i] != '\n')
	{

		(*i)++;
	}
	return (SUCCESS);
}
