#ifndef LEM_IN_H
# define LEM_IN_H

# include "../libft/libft.h"

# define BUF_SIZE	256
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
	struct s_room	*ancestor;
	t_list			*nghbr;
	char			*name;
	int				x;
	int				y;
	int				ant	: 29;
	int				status	:  3;
}				t_room;

typedef struct	s_edge
{
	t_room	*room;
	int		flow;
}				t_edge;

typedef struct	s_parser
{
	t_room	*start;
	t_room	*end;
	char	*last_line;
	t_bool	malloced;
	int		ants;
	int		ret		: 27;
	int		status	:  3;
	int		steps	:  2;
}				t_parser;

/*
**	Memory.c functions
*/

t_parser		*init_parser(void);
t_room			*init_room(char *name, const int status);
t_edge			*init_edge(t_room *room);
void			del_room(t_room **room);
void			btree_deep_del(t_btree **root);

/*
**	Parsing functions
*/

int				ft_read_stdin(t_btree **graph, t_parser *data);
int				ft_buf_parser(char *buf, t_parser * data, t_btree **graph);
int				ft_register_ants(const char *buf, int *i, t_parser *data);
int				ft_register_room(const char *buf, int *i, t_parser *data, t_btree **graph);
int				ft_register_com(const char *buf, int *i, t_parser *data);
int				ft_register_coord(const char *buf, int *i, t_room *room,
					const char limit);
int				ft_register_path(const char *buf, int *i, t_btree **graph, t_parser *data);
int				ft_save_data(const char *buf, t_parser *data, int *i);

/*
**	B_tree tools functions
*/

int				ft_btreecmp(const void *struct1, const void *struct2);
int				ft_btreeccmp_hyphen(const void *struc, const void *str);
int				ft_btreeccmp_newline(const void *struc, const void *str);
int				ft_strccmp(const char *s1, const char *s2, const char limit);
t_bool			ft_lst_node_exists(t_list *head, t_room *node);
t_bool			ft_lst_edge_exists(t_list *head, t_room *node);
int				ft_fill_neighbours(t_list **head, t_list *to_add);
t_bool			ft_bfs(t_parser *data);
int				flow_direction(t_parser *data);
int				edmondkarp(t_parser *data);
int				push_colony(t_parser *data);

// void			ft_lst_push_back(t_list **head, t_room *new);

/*
**	FOR TESTING PURPOSE
*/

void		print_btree(void *data); // in main.c
void		print_list(t_list *head); // in check_validity.c


#endif
