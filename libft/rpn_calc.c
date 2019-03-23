#include "libft.h"

int		operations(int a, int b, char c, int *ret)
{
	if (c == '+')
		*ret = a + b;
	else if (c == '-')
		*ret = a - b;
	else if (c == '*')
		*ret = a * b;
	else if (c == '/')
	{
		if (b == 0)
			return (0);
		*ret = a / b;
	}
	else if (c == '%')
	{
		if (b == 0)
			return (0);
		*ret = a % b;
	}
	return (1);
}

int		check(char *str)
{
	if (*str == ' ')
		return (0);
	while (*str)
	{
		if (*str != '+' && *str != '-' && *str != '*' && *str != '/'
					&& *str != '%' && *str != ' ' && (*str < '0' || *str > '9'))
			return (0);
		str++;
	}
	return (1);
}

int		parsing(char *str)
{
	t_stack	*current;
	int	ret;

	current = NULL;
	if (check(str) == 0)
	{
		ft_putendl("Error");
		return (0);
	}
	while (*str)
	{
		while (*str && *str == ' ')
			str++;
		if ((*str >= '0' && *str <= '9') || (*str == '-' && *(str + 1) >= '0' && *(str + 1) <= '9'))
		{
			manage_stack(&current, atoi(str));
			if (*str == '+' || *str == '-')
				str++;
			while (*str && *str >= '0' && *str <= '9')
				str++;
		}
		else if (*str && (*str == '+' || *str == '-' || *str == '*' || *str == '/' || *str == '%'))
		{
			if (current && current->next)
			{
				if ((operations(current->next->nb, current->nb, *str, &ret)) == 0)
				{
					printf("Error\n");
					free_stack(&current);
					return (0);
				}
				destack(&current);
				manage_stack(&current, ret);
				str++;
			}
			else
			{
				printf("Error\n");
				free_stack(&current);
				return (0);
			}
		}
		else
			str++;
	}
	if (current == NULL || current->next != NULL)
		printf("Error\n");
	else
		printf("%i\n", ret);
	free_stack(&current);
	return (ret);
}
