#include "../includes/lem_in.h"

t_parser	*init_parser(void)
{
	t_parser	*new;

	if (!(new = (t_parser*)malloc(sizeof(*new))))
		return (NULL);
	new->ants	= -1;
	new->status	=  0;
	new->steps	=  0;
	new->ret	=  0;
	new->start = NULL;
	new->end = NULL;
	new->last_line = NULL;
	new->end_of_file = 0;
	return (new);
}

t_room		*init_room(char *name, const int status)
{
	t_room	*new;

	if (!(new = (t_room*)malloc(sizeof(*new))))
		return (NULL);
	new->name = name;
	new->x = 0;
	new->y = 0;
	new->filled = false;
	new->nghbr = NULL;
	new->status = status;
	return (new);
}

void		del_room(t_room **room)
{
	ft_strdel(&(*room)->name);
	ft_lstdel(&(*room)->nghbr, NULL);
	ft_memdel((void*)room);
}

void	btree_deep_del(t_btree **root)
{
	if (root && *root)
	{
		if ((*root)->left)
			btree_deep_del(&(*root)->left);
		if ((*root)->right)
			btree_deep_del(&(*root)->right);
		del_room((t_room**)&(*root)->data);
		ft_memdel((void*)root);
	}
}
