#include "../includes/lem_in.h"

int		ft_strccmp(const char *s1, const char *s2, const char limit)
{
	while (*s1 && *s2 && *s1 == *s2 && *s2 != limit)
	{
		s1++;
		s2++;
	}
	return ((unsigned char)*s1 - (unsigned char)*s2);
}
