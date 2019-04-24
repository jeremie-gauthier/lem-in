#include "../includes/lem_in.h"

int		ft_set_err_code(t_parser *data, int code)
{
	data->err_code = code;
	return (FAIL);
}

void	*ft_set_err_code_ptr(t_parser *data, int code)
{
	data->err_code = code;
	return (NULL);
}
