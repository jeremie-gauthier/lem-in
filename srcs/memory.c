#include "../includes/lem_in.h"

t_parser	*init_parser(void)
{
	t_parser	*new;

	if (!(new = (t_parser*)malloc(sizeof(*new))))
		return (NULL);
	new->ants	= -1;
	new->start	=  0;
	new->end	=  0;
	new->steps	=  0;
	new->ret	=  0;
	return (new);
}

t_room		*init_room(const char *name, const int status)
{
	t_room	*new;

	if (!(new = (t_room*)malloc(sizeof(*new))))
		return (NULL);
	new->name = ft_strdup(name);
	new->x = 0;
	new->y = 0;
	new->filled = false;
	new->nghbr = NULL;
	new->status = status;
	return (new);
}
