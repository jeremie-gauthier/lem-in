#include "../includes/lem_in.h"

//faire un check pour savoir s'il y a bien un \n dans le cdup (line).
//car il est possible que nous ne copions qu'une partie de la ligne si le buf_size est trop petit
int		ft_restore_data(const char *buf, t_parser *data, int *i)
{
	char	*line;
	int		j;

	if (!(line = ft_strcdup(buf, '\n')))
		return (FAIL);
	if (!(line = ft_strjoin_free(data->last_line, line)))
	{
		ft_strdel(&line);
		return (FAIL);
	}
	j = 0;
	while (buf[j] && buf[j] != '\n')
		j++;
	if (buf[j] == '\n')
		*i += j + 1;
	else
		*i += j;
	ft_printf("CONCAT LINE = |%s|\n", line);
	return (SUCCESS);
}