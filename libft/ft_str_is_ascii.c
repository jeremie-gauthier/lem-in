#include "libft.h"

int		ft_str_is_ascii(const char *str)
{
	while (*str)
	{
		if (!ft_isascii(*str))
			return (0);
		str++;
	}
	return (1);
}