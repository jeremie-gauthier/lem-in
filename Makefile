NAME	=	lem-in

SOURCES	=	main.c\
			memory.c\
			ft_btreecmp.c\
			ft_strccmp.c\
			read_stdin.c\
			buf_parser.c\
			register_ants.c\
			register_room.c\
			register_coord.c\
			register_com.c\
			register_path.c\
			save_data.c\
			ft_fill_neighbours.c\
			ft_lst_node_exists.c\
			breadth_first_search.c\
			set_flow.c\
			edmondkarp.c\
			colony.c

DIR_C	=	srcs

DIR_H	=	includes

DIR_O	=	temporary

SRCS	=	$(addprefix $(DIR_C)/,$(SOURCES))

OBJS	=	$(addprefix $(DIR_O)/,$(SRCS:.c=.o))

CC		=	gcc

CFLAGS	=	-Wall -Werror -Wextra

LIB_PATH=	libft

LIB		=	$(LIB_PATH)/libft.a

HDR		=	$(DIR_H)/lem_in.h

RM		=	rm -rf

CLEAN	=	clean

all:		$(NAME)

$(LIB):
			@make -C $(LIB_PATH)

$(NAME):	$(LIB) $(OBJS) $(HDR) Makefile
			@$(CC) $(CFLAGS) -I$(DIR_H) -o $(NAME) $(SRCS) $(LIB)
			@echo "Lem-in		: lem-in file has been successfully created."

$(DIR_O)/%.o: %.c
			@mkdir -p temporary
			@mkdir -p temporary/srcs
			@$(CC) $(CFLAGS) -I$(DIR_H) -o $@ -c $<

clean:	
			@$(RM) $(DIR_O)
			@make clean -C $(LIB_PATH)
			@echo "Lem-in		: *.o files have been deleted."

fclean:		clean
			@$(RM) $(NAME)
			@make fclean -C $(LIB_PATH)
			@echo "Lem-in		: lem-in file has been deleted."

re:			fclean all

.PHONY: all clean fclean re
