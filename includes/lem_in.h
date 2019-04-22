/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jergauth <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/19 14:06:32 by jergauth          #+#    #+#             */
/*   Updated: 2019/04/19 14:06:34 by jergauth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEM_IN_H
# define LEM_IN_H

# include "../libft/libft.h"

# define BUF_SIZE	4096
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
	int				tmp_capacity;
	int				capacity;
	int				ant;
	int				status : 3;
	unsigned int	room_used : 1;
	unsigned int	vertex_used : 1;
}				t_room;

typedef struct	s_edge
{
	t_room			*room;
	int				tmp_flow : 16;
	int				flow : 16;
}				t_edge;

typedef struct	s_parser
{
	t_room			*start;
	t_room			*end;
	char			*last_line;
	t_bool			malloced;
	int				ants;
	int				ret : 26;
	int				status : 3;
	int				steps : 2;
	unsigned int	room_temoin : 1;
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
int				ft_buf_parser(char *buf, t_parser *data, t_btree **graph);
int				ft_register_ants(const char *buf, int *i, t_parser *data);
int				ft_register_room(const char *buf, int *i, t_parser *data,
					t_btree **graph);
int				ft_register_com(const char *buf, int *i, t_parser *data);
int				ft_register_coord(const char *buf, int *i, t_room *room,
					const char limit);
int				ft_register_path(const char *buf, int *i, t_btree **graph,
					t_parser *data);
int				ft_save_data(const char *buf, t_parser *data, int *i);
int				ft_strlimit(const char *str, const char limit);
int				ft_strccmp(const char *s1, const char *s2, const char limit);

/*
**	B_tree tools functions
*/

int				ft_btreecmp(const void *struct1, const void *struct2);
int				ft_btreeccmp_hyphen(const void *struc, const void *str);
int				ft_btreeccmp_newline(const void *struc, const void *str);

/*
**	Algorithm
*/

t_bool			ft_lst_node_exists(t_list *head, t_room *node);
t_bool			ft_lst_edge_exists(t_list *head, t_room *node);
int				ft_fill_neighbours(t_list **head, t_list *to_add);
t_bool			ft_bfs(t_parser *data);
int				flow_direction(t_parser *data);
int				edmondkarp(t_parser *data);
int				push_colony(t_parser *data);
t_room			*get_next_room(t_room *room);
int				ft_balance_flow(t_parser *data);
int				detect_vertex_separator(t_parser *data);
void			ft_keep_flow(t_parser **data);
int				ft_predict_tours(t_parser *data);
void			ft_redistribute_flux(t_parser *data, int tmp_ants,
					t_room *best_path);
int				ft_ants_repartition(t_parser *data, int flow_max);

/*
**	FOR TESTING PURPOSE
*/

void			print_btree(void *data); // in main.c
void			print_list(t_list *head); // in check_validity.c

#endif
