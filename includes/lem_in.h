#ifndef __LEM_IN_H__
# define __LEM_IN_H__

# include "../libft/libft.h"

# define BUF_SIZE	256
# define COMMENTARY	"##"
# define START		"##start"
# define STOP		"##stop"

typedef struct	s_parser
{
	int		ants;
	int		start	:  2;
	int		stop	:  2;
	int		steps	:  2;
	int		ret		: 26;
}				t_parser;

typedef struct	s_room
{
	char	*name;
	int		x;
	int		y;
	t_bool	filled;
	t_list	*nghbr;
	char	status;
}				t_room;

/*
**	Memory.c functions
*/

t_parser		*init_parser(void);

int				read_stdin(t_btree **graph);
int				register_ants(const char *buf, int *i, t_parser *data);

#endif