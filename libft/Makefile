NAME		=	libft.a

CC			=	gcc

CFLAGS		=	-Wall -Wextra -Werror -D BUFFER_SIZE=1024

SRCS		=	ft_memset.c ft_bzero.c ft_memcpy.c ft_memccpy.c ft_memmove.c ft_calloc.c ft_memchr.c ft_memcmp.c ft_strlen.c ft_strdup.c ft_strlcat.c ft_strlcpy.c ft_strchr.c ft_strrchr.c ft_strnstr.c ft_strncmp.c ft_atoi.c ft_isalpha.c ft_isdigit.c ft_isalnum.c ft_isascii.c ft_tolower.c ft_toupper.c ft_isprint.c ft_substr.c ft_strndup.c ft_strmapi.c ft_strjoin.c ft_strcat.c ft_strtrim.c ft_split.c ft_itoa.c ft_putchar_fd.c ft_putstr_fd.c ft_putendl_fd.c ft_putnbr_fd.c ft_isspace.c ft_atoi_base.c ft_indexof.c ft_putchar.c ft_putstr.c ft_itoa_base.c ft_puts.c ft_starts_with.c ft_ends_with.c ft_strmerge.c ft_strcpy.c ft_putnbr.c ft_contains.c get_next_line.c get_next_line_utils.c ft_split_utils.c rad.c ft_strcmp.c swap.c abs.c

OBJS    	=   $(SRCS:.c=.o)

BONUS_SRCS	=	ft_lstnew.c ft_lstadd_front.c ft_lstsize.c ft_lstlast.c ft_lstadd_back.c ft_lstdelone.c ft_lstclear.c ft_lstiter.c ft_lstmap.c

BONUS_OBJS	=	$(BONUS_SRCS:.c=.o)

.c.o:
				$(CC) $(CFLAGS) -c $< -o $(<:.c=.o)

all:			$(NAME)

$(NAME):		$(OBJS)
				ar rc $(NAME) $(OBJS)

clean:
				rm -f $(OBJS) $(BONUS_OBJS)

fclean:			clean
				rm -f $(NAME)

re:				fclean all

bonus:			$(NAME) $(BONUS_OBJS)
				ar r $(NAME) $(BONUS_OBJS)

.PHONY:     	all clean fclean re
