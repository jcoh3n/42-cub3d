NAME = cub3D

CC = cc
CFLAGS = -Wall -Wextra -Werror -I./includes -I./lib/libft -I./lib/minilibx-linux
LDFLAGS = -L./lib/libft -L./lib/minilibx-linux
LDLIBS = -lft -lmlx -lXext -lX11 -lm

# Source files
SRC_DIR = src
SRCS = main.c parsing.c parse_colors.c parse_textures.c \
       map_validation.c map_flood_fill.c map_consistency.c map_store.c

# Object files
OBJ_DIR = objs
OBJS = $(addprefix $(OBJ_DIR)/, $(SRCS:.c=.o))

# Colors
GREEN = \033[0;32m
BLUE = \033[0;34m
RESET = \033[0m

all: $(OBJ_DIR) libs $(NAME)

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

libs:
	@echo "$(BLUE)Compiling libft...$(RESET)"
	@make -sC lib/libft
	@echo "$(BLUE)Compiling minilibx...$(RESET)"
	@make -sC lib/minilibx-linux >/dev/null 2>&1

$(NAME): $(OBJS)
	@echo "$(BLUE)Linking $(NAME)...$(RESET)"
	@$(CC) $(OBJS) $(LDFLAGS) $(LDLIBS) -o $(NAME)
	@echo "$(GREEN)Build successful!$(RESET)"

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@echo "$(BLUE)Compiling $<...$(RESET)"
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@echo "$(BLUE)Cleaning object files...$(RESET)"
	@make -sC lib/libft clean
	@make -sC lib/minilibx-linux clean >/dev/null 2>&1
	@rm -rf $(OBJ_DIR)

fclean: clean
	@echo "$(BLUE)Cleaning executables...$(RESET)"
	@make -sC lib/libft fclean
	@rm -f $(NAME)
	@echo "$(GREEN)Clean successful!$(RESET)"

re: fclean all

.PHONY: all clean fclean re libs 