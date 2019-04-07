#include "libft.h"

t_list	*ft_lstnew_addr(void *content)
{
	t_list	*node;

	if (!(node = (t_list*)malloc(sizeof(*node))))
		return (NULL);
	node->content = content;
	node->content_size = 0;
	node->next = NULL;
	return (node);
}
