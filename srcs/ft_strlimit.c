#include "../includes/lem_in.h"

int		ft_strlimit(const char *str, const char limit)
{
	int i;

	i = 0;
	while (str && str[i] && str[i] != limit)
		i++;
	return (i);
}
