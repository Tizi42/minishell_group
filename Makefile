NAME	=	msh
CC		=	gcc
CFLAGS	=	-Wall -Werror -Wextra -g
OBJ_DIR	=	obj/
SRC_DIR	=	src/
SRCS	+=	main.c error.c error2.c tool.c
SRCS	+=	parser/parse.c parser/parse2.c parser/tool_parse.c parser/tool_parse2.c parser/tool_parse_split.c parser/tool_token.c parser/tool_tknlst.c  parser/tool_str.c parser/tool_syntax.c
SRCS	+=	executer/execute.c executer/path_search.c executer/io.c executer/io2.c
SRCS	+=	builtins/builtins.c builtins/builtins2.c builtins/unset.c
OBJS    =	$(addprefix $(OBJ_DIR), $(SRCS:.c=.o))
LIBS	=	-lreadline -Llibft -lft
INC		=	-Iinclude -Ilibft

$(OBJ_DIR)%.o:	$(SRC_DIR)%.c
	mkdir -p $(OBJ_DIR)/parser
	mkdir -p $(OBJ_DIR)/executer
	mkdir -p $(OBJ_DIR)/builtins
	$(CC) -c $(INC) $(CFLAGS) $< -o $@

all:		$(NAME)

$(NAME):	$(OBJS)
	make bonus -C libft
	$(CC) $(CFLAGS) $(INC) $^ $(LIBS) -o $(NAME)

clean:
	make clean -C libft
	rm -rf $(OBJ_DIR)

fclean:		clean
	make fclean -C libft
	rm -f $(NAME)

re:			fclean all
