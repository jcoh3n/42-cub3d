NAME = cub3D

CC = cc
CFLAGS = -Wall -Wextra -Werror -I./includes -I./lib/libft -I./lib/minilibx-linux
LDFLAGS = -L./lib/libft -L./lib/minilibx-linux
LDLIBS = -lft -lmlx -lXext -lX11 -lm

SRCS = src/main.c \
       src/parsing.c

OBJS = $(SRCS:.c=.o)

all: libs $(NAME)

libs:
	@make -C lib/libft
	@make -C lib/minilibx-linux

$(NAME): $(OBJS)
	$(CC) $(OBJS) $(LDFLAGS) $(LDLIBS) -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	@make -C lib/libft clean
	@make -C lib/minilibx-linux clean
	rm -f $(OBJS)

fclean: clean
	@make -C lib/libft fclean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re libs 