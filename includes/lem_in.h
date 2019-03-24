#ifndef LEM_IN_H
# define LEM_IN_H

# include "../libft/libft.h"

# define BUF_SIZE	256
# define FAIL		0
# define SUCCESS	1
# define COMMENTARY	"##"
# define START		"##start"
# define END		"##end"

typedef struct	s_parser
{
	int		ants;
	int		start	:  2;
	int		end		:  2;
	int		steps	:  1;
	int		ret		: 27;
}				t_parser;

typedef struct	s_room
{
	char	*name;
	int		x;
	int		y;
	t_bool	filled;
	t_list	*nghbr;
	int		status;
}				t_room;

/*
**	Memory.c functions
*/

t_parser		*init_parser(void);
t_room			*init_room(char *name, const int status);

/*
**	Parsing functions
*/

int				ft_read_stdin(t_btree **graph);
int				ft_buf_parser(const char *buf, t_parser * data, t_btree **graph);
int				ft_register_ants(const char *buf, int *i, t_parser *data);
int				ft_register_room(const char *buf, int *i, t_parser *data, t_btree **graph);

/*
**	B_tree tools functions
*/

int				ft_btreecmp(const void *struct1, const void *struct2);

#endif
