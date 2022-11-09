SRCS	=	checkgrid.c renderstuff.c
OBJS	=	${SRCS:.c=.o}
RM		=	rm -f
CC		=	cc
CFLAGS	=	-Wall -Wextra -Werror -g
DFLAGS    =    -L./minilibx-linux -lmlx -lXext -lX11 -lm
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
	${CC} checkgrid.c ${CFLAGS} ${NAME} ${DFLAGS} -lbsd
	./a.out map.ber


val: all
	valgrind --leak-check=full \
		--show-leak-kinds=all \
		--track-origins=yes \
		--verbose \
		--log-file=valgrind-out.txt \
		./a.out map.ber

	
.PHONY: all clean fclean re so_long
	./a.out 