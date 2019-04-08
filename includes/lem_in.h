#ifndef LEM_IN_H
# define LEM_IN_H

# include "../libft/libft.h"

# define BUF_SIZE	16
# define FAIL		0
# define SUCCESS	1
# define COMMENTARY	"#"
# define START_COM	"##start\n"
# define END_COM	"##end\n"
# define START_STR	"start"
# define END_STR	"end"
# define LAMBDA		0
# define START		1
# define END		2
# define RIGHT		0
# define LEFT		1

typedef struct	s_room
{
	char	*name;
	int		x;
	int		y;
	t_bool	filled;
	t_list	*nghbr;
	int		status;
}				t_room;

typedef struct	s_parser
{
	int		ants;
	int		status	:  3;
	int		steps	:  2;
	int		ret		: 27;
	t_room	*start;
	t_room	*end;
	char	*last_line;
}				t_parser;

/*
**	Memory.c functions
*/

t_parser		*init_parser(void);
t_room			*init_room(char *name, const int status);
void			del_room(t_room **room);
void			btree_deep_del(t_btree **root);

/*
**	Parsing functions
*/

int				ft_read_stdin(t_btree **graph, t_parser *data);
int				ft_buf_parser(const char *buf, t_parser * data, t_btree **graph);
int				ft_register_ants(const char *buf, int *i, t_parser *data);
int				ft_register_room(const char *buf, int *i, t_parser *data, t_btree **graph);
int				ft_register_com(const char *buf, int *i, t_parser *data);
int				ft_register_coord(const char *buf, int *i, t_room *room,
					const char limit);
int				ft_register_path(const char *buf, int *i, t_btree **graph, t_parser *data);
int		ft_save_data(const char *buf, t_parser *data);
int		ft_restore_data(const char *buf, t_parser *data);

/*
**	B_tree tools functions
*/

int				ft_btreecmp(const void *struct1, const void *struct2);
int				ft_btreeccmp_hyphen(const void *struc, const void *str);
int				ft_btreeccmp_newline(const void *struc, const void *str);
int				ft_strccmp(const char *s1, const char *s2, const char limit);

/*
**	FOR TESTING PURPOSE
*/

void		print_btree(void *data);

#endif
