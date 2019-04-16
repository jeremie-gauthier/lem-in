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
	new->malloced = false;
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
	new->ancestor = NULL;
	return (new);
}

t_edge		*init_edge(t_room *room)
{
	t_edge	*new;

	if (!(new = (t_edge*)malloc(sizeof(*new))))
		return (NULL);
	new->room = room;
	new->flow = 0;
	return (new);
}

void		del_room(t_room **room)
{
	t_list	*current;
	t_list	*tmp;

	ft_strdel(&(*room)->name);
	current = (*room)->nghbr;
	while (current)
	{
		tmp = current->next;
		ft_memdel((void*)current);
		current = tmp;
	}
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
