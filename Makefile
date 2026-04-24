# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mickzhan <mickzhan@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/12/05 13:00:27 by mickzhan          #+#    #+#              #
#    Updated: 2026/04/24 15:32:12 by mickzhan         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.SILENT:

NAME = cub3D
CC = cc
CFLAGS = -Wall -Werror -Wextra -I./includes -I./libft -g3
SRC_DIR = src/
SRC =	main.c \
		parsing/map_reader.c \
		
		
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
	@rm -rf $(OBJ)
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
