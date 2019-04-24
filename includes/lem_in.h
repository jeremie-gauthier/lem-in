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

# define BUF_SIZE	8192
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
# define AUTO_COLOR	"-c"
# define LINE_COUNT	"-l"
# define VERBOSE	"-v"

typedef enum	e_colors
{
	none = -1,
	red = 0,
	green = 1,
	yellow = 2,
	blue = 3,
	magenta = 4,
	cyan = 5
}				t_colors;

typedef struct	s_room
{
	struct s_room	*ancestor;
	t_list			*nghbr;
	char			*name;
	t_colors		color;
	int				x;
	int				y;
	int				tmp_capacity;
	int				capacity;
	int				ant;
	int				len_path;
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
	t_colors		color_next_room;
	int				ants;
	int				ret : 17;
	unsigned int	status : 2;
	unsigned int	room_temoin : 1;
	unsigned int	steps : 1;
	unsigned int	start_set : 1;
	unsigned int	end_set : 1;
	unsigned int	color_auto : 1;
	unsigned int	line_count : 1;
	unsigned int	verbose : 1;
	unsigned int	err_code : 6;
}				t_parser;

/*
**	Memory.c functions
*/

t_parser		*init_parser(void);
t_room			*init_room(char *name, t_parser *data);
t_edge			*init_edge(t_room *room);
t_room			**init_roomtab(t_parser *data, int len);
void			del_room(t_room **room);
void			btree_deep_del(t_btree **root);
void			reset_previous_data(t_room **tab, int len);

/*
**	Parsing functions
*/

int				ft_set_err_code(t_parser *data, int code);
void			*ft_set_err_code_ptr(t_parser *data, int code);
int				ft_parse_args(char **argv, t_parser *data);
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
int				detect_vertex_separator(t_parser *data);
void			ft_keep_flow(t_room *room, t_parser *data);
void			set_len_path(t_parser *data);
int				ft_get_nb_flows(t_parser *data);
void			ft_sort_roomtab(t_room **tab, int len);
int				ft_ants_repartition(t_parser *data, int *max_tours);

#endif
