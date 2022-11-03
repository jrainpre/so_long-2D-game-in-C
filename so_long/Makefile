SRCS	=	checkgrid.c
OBJS	=	${SRCS:.c=.o}
RM		=	rm -f
CC		=	cc
CFLAGS	=	-Wall -Wextra -Werror -g
NAME	=	so_long.a
MAKELIB	=	cd libft && make

${NAME}:	${OBJS}
	${MAKELIB} all
	cp libft/libft.a ${NAME}
	ar rc ${NAME} ${OBJS}

all: ${NAME}

clean:
	${MAKELIB} clean
	${RM} ${OBJS}

fclean: clean
	${MAKELIB} fclean
	${RM} ${NAME} a.out
	
re: fclean all

test: ${NAME}
	${CC} ${CFLAGS} checkgrid.c ${NAME} -lbsd

	
.PHONY: all clean fclean re so_long
	./a.out 