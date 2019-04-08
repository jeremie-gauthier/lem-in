#include "libft.h"

char	*ft_strcdup(const char *str, const char limit)
{
	size_t	len;
	size_t	i;
	char	*dup;

	if (str == NULL)
		return (NULL);
	len = 0;
	while (str[len] && str[len] != limit)
		len++;
	if (!(dup = (char*)malloc(sizeof(*dup) * len + 1)))
		return (NULL);
	i = 0;
	while (i < len)
	{
		dup[i] = str[i];
		i++;
	}
	dup[i] = '\0';
	return (dup);
}
