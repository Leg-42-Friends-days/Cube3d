# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mickzhan <mickzhan@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/12/05 13:00:27 by mickzhan          #+#    #+#              #
#    Updated: 2026/05/15 15:21:08 by mickzhan         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.SILENT:

NAME = cub3D
CC = cc
CFLAGS = -Wall -Wextra -Werror -Wno-cast-function-type -I./includes -I./libft -g3
SRC_DIR = src/
SRC =	main.c \
		hook.c \
		load_textures.c \
		parsing/map_read.c \
		parsing/map_start.c \
		parsing/error_utils.c \
		parsing/error_utils2.c \
		parsing/free_parsing.c \
		parsing/texture_read.c \
		parsing/rgb_fonction.c \
		parsing/flood_fill_cub.c \
		parsing/texture_copy.c \
		parsing/parsing_utils.c \
		parsing/parsing_utils2.c \
		parsing/init_parser.c \
		parsing/bonus_parsing.c \
		minimap/minimap.c \
		minimap/minimap_utils.c \
		raycasting/raycasting.c \
		raycasting/init_raycasting.c \
		raycasting/print_wall.c \
		raycasting/print_wall_utils.c \
		raycasting/walk.c \
		raycasting/collision_detection.c

OBJ_DIR = obj/
OBJ = $(addprefix $(OBJ_DIR), $(SRC:.c=.o))

# Libft
LIBFT_DIR = libft
LIBFT = $(LIBFT_DIR)/libft.a
LIBFT_FLAGS = -L./$(LIBFT_DIR) -lft


# Minilibx on Linux
MLX_DIR = minilibx-linux
MLX_REPO = https://github.com/42paris/minilibx-linux.git
MLX_FLAGS = -L./$(MLX_DIR) -lmlx -lXext -lX11 -lm


all: minilibx libft $(NAME)

$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -c $< -o $@
	
$(NAME): $(OBJ) $(LIBFT)
	@$(CC) $(OBJ) $(CFLAGS) $(MLX_FLAGS) $(LIBFT_FLAGS) -o $(NAME)
	@echo "✅ $(NAME) ready !"

clean:
	@rm -rf $(OBJ) $(OBJ_DIR)
	@$(MAKE) -C $(LIBFT_DIR) clean
	@echo "✅ Removed object files"

fclean: clean
	@rm -f $(NAME)
	@rm -rf $(MLX_DIR)
	@$(MAKE) -C $(LIBFT_DIR) fclean
	@echo "✅ Removed executable $(NAME)"
	@echo "✅ Removed folder $(MLX_DIR)"

re: fclean all

minilibx:
	@if [ ! -d "$(MLX_DIR)" ]; then \
		echo "Cloning $(MLX_REPO)..."; \
		git clone $(MLX_REPO); \
	else \
		echo "️️⚠️  $(MLX_DIR) already exists, skipping clone."; \
	fi
	@echo "🔧 Building $(MLX_DIR)..."
	@$(MAKE) -C $(MLX_DIR) --no-print-directory > /dev/null 2>&1

val:
	valgrind --trace-children=yes --leak-check=full --track-origins=yes --track-fds=yes --show-leak-kinds=all ./$(NAME) $(ARGS) || true
	
libft:
	@$(MAKE) -C $(LIBFT_DIR) --no-print-directory

.PHONY: all clean fclean re minilibx val libft
