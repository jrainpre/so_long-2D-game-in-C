SRCS	=	srcs/player_control.c srcs/window_utils.c srcs/get_map.c srcs/checkgrid1.c srcs/checkgrid2.c srcs/grid_utils.c srcs/search_solutions.c srcs/main.c
OBJS    =     $(SRCS:.c=.o)
RM        =    rm -f
CC        =    cc
CFLAGS    =    -Wall -Wextra -Werror -g
NAME    =    so_long
DFLAGS    =    -L./minilibx-linux -lmlx -lXext -lX11 -lm

all: $(NAME)

$(NAME):
	$(MAKE) all -C ./libft
	$(CC) -o $(NAME) $(CFLAGS) $(SRCS) $(DFLAGS) ./libft/libft.a

clean:
	$(MAKE) clean -C ./libft
	$(RM) $(OBJS)

fclean: clean
	$(MAKE) fclean -C ./libft
	$(RM) $(NAME)
    
re: fclean all

test: $(NAME)
	./so_long maps/map.ber

val: all
	valgrind --leak-check=full \
		--show-leak-kinds=all \
		--track-origins=yes \
		--verbose \
		--log-file=valgrind-out.txt \
		./so_long maps/map.ber
    
.PHONY: all clean fclean re so_long test val