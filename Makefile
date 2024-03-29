NAME	=	msh
CC		=	cc
CFLAGS	=	-Wall -Werror -Wextra -g
OBJ_DIR	=	obj/
SRC_DIR	=	src/
SRCS	+=	main.c error.c error2.c tool.c signals.c clean.c init.c
SRCS	+=	parser/parse.c parser/parse2.c parser/tool_cml_redi.c parser/tool_heredoc.c parser/split.c parser/token.c parser/tknlst.c  parser/tool_str.c parser/tool_str2.c parser/syntax.c parser/heredoc.c
SRCS	+=	executer/execute.c executer/execute2.c executer/io.c executer/io2.c
SRCS	+=	builtins/builtins.c builtins/builtins2.c builtins/unset.c builtins/export_utils.c
OBJS    =	$(addprefix $(OBJ_DIR), $(SRCS:.c=.o))
LIBS	=	-lreadline -Llibft -lft
INC		=	-Iinclude -Ilibft

$(OBJ_DIR)%.o:	$(SRC_DIR)%.c
	mkdir -p $(OBJ_DIR)parser
	mkdir -p $(OBJ_DIR)executer
	mkdir -p $(OBJ_DIR)builtins
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
