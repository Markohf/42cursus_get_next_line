SRCS		= 	get_next_line.c			\
				get_next_line_utils.c	\

OBJS		=	$(SRCS:.c=.o)

LIB			=	get_next_line.h
CC			=	cc
RM			=	rm -f
CFLAGS		=	-Wall -Wextra -Werror

NAME		=	get_next_line.a

all:			$(NAME)

$(NAME):		$(OBJS) $(LIB)
				ar rcs $(NAME) $(OBJS)

clean:
				$(RM) $(OBJS)

fclean:			clean
				$(RM) $(NAME)

re:				fclean $(NAME)

.PHONY:			all clean fclean re