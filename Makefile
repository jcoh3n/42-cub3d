NAME = cub3D

CC = cc
CFLAGS = -Wall -Wextra -Werror -g3 -I./includes -I./lib/libft -I./lib/minilibx-linux
LDFLAGS = -L./lib/libft -L./lib/minilibx-linux
LDLIBS = -lft -lmlx -lXext -lX11 -lm

# Source files
SRCS = src/main.c \
	   src/clean/ft_cleanup.c \
	   src/clean/ft_cleanup2.c \
       src/parsing/parsing.c \
       src/parsing/parse_textures.c \
       src/parsing/parse_colors.c \
       src/parsing/map_validation.c \
       src/parsing/map_store.c \
       src/parsing/map_flood_fill.c \
       src/parsing/map_consistency.c \
       src/window/window_init.c \
	   src/window/window_init2.c \
       src/window/window_events.c \
       src/window/mouse_events.c \
       src/window/buffer_management.c \
       src/window/window_utils.c \
       src/player/player_init.c \
       src/player/player_movement.c \
       src/utils/utils.c \
	   src/utils/map_consistency_utils.c \
	   src/utils/map_store_utils.c \
	   src/utils/parse_colors_utils.c \
       src/minimap/minimap.c \
       src/minimap/minimap_drw_utils.c \
       src/minimap/minimap_draw.c \
       src/minimap/minimap_init.c \
       src/window/render.c \
       src/raycasting/raycasting.c \
       src/raycasting/render/wall_render.c \
       src/raycasting/render/texture_utils.c \
       src/raycasting/render/draw_utils.c \
       src/raycasting/dda/dda_utils.c \


# Object files
OBJ_DIR = objs
OBJS = $(SRCS:src/%.c=$(OBJ_DIR)/%.o)

# Library files
LIBFT = lib/libft/libft.a
MLX = lib/minilibx-linux/libmlx.a

# Colors
GREEN = \033[0;32m
BLUE = \033[0;34m
RESET = \033[0m

all: $(NAME)

$(OBJ_DIR)/%.o: src/%.c
	@mkdir -p $(dir $@)
	@echo "$(BLUE)Compiling $<...$(RESET)"
	@$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJ_DIR) $(LIBFT) $(MLX) $(OBJS)
	@echo "$(BLUE)Linking $(NAME)...$(RESET)"
	@$(CC) $(OBJS) $(LDFLAGS) $(LDLIBS) -o $(NAME)
	@echo "$(GREEN)Build successful!$(RESET)"

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)
	@mkdir -p $(OBJ_DIR)/parsing
	@mkdir -p $(OBJ_DIR)/window
	@mkdir -p $(OBJ_DIR)/player
	@mkdir -p $(OBJ_DIR)/clean
	@mkdir -p $(OBJ_DIR)/utils
	@mkdir -p $(OBJ_DIR)/minimap
	@mkdir -p $(OBJ_DIR)/raycasting
	@mkdir -p $(OBJ_DIR)/raycasting/render
	@mkdir -p $(OBJ_DIR)/raycasting/dda

$(LIBFT):
	@echo "$(BLUE)Compiling libft...$(RESET)"
	@make -sC lib/libft

$(MLX):
	@echo "$(BLUE)Compiling minilibx...$(RESET)"
	@make -sC lib/minilibx-linux >/dev/null 2>&1

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

.PHONY: all clean fclean re