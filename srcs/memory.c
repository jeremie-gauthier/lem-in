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
