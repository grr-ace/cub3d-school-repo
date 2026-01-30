# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: grmullin <grmullin@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/03/20 11:56:36 by grmullin          #+#    #+#              #
#    Updated: 2025/07/04 20:01:44 by grmullin         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# ==== CONFIG ====
NAME = cub3D
CC = cc
CFLAGS = -Wall -Wextra -Werror -g
INCLUDES = -I./includes

# ==== SOURCE FILES ====
SRCS = src/main.c \
	src/parsing/parse_file.c \
	src/parsing/parse_textures.c \
	src/parsing/parse_colors.c \
	src/parsing/parse_map.c \
	src/parsing/parse_player.c \
	src/parsing/parsing_utils.c \
	src/parsing/parsing_utils1.c \
	src/utils/utils.c \
	src/utils/get_next_line.c \
	src/utils/mlx_utils.c \
	src/utils/free.c \
	src/rendering/get_wall_distance.c \
	src/rendering/player_movement.c \
	src/rendering/render_textures.c \
	src/rendering/render_game.c \
	src/rendering/render_view.c \
	src/rendering/render_utils.c

SRCS_BONUS = src_bonus/main.c \
	src_bonus/parsing/parse_file.c \
	src_bonus/parsing/parse_textures.c \
	src_bonus/parsing/parse_colors.c \
	src_bonus/parsing/parse_map.c \
	src_bonus/parsing/parse_player.c \
	src_bonus/parsing/parsing_utils.c \
	src_bonus/parsing/parsing_utils1.c \
	src_bonus/utils/utils.c \
	src_bonus/utils/get_next_line.c \
	src_bonus/utils/mlx_utils.c \
	src_bonus/utils/free.c \
	src_bonus/rendering/check_walls.c \
	src_bonus/rendering/get_wall_distance.c \
	src_bonus/rendering/player_movement.c \
	src_bonus/rendering/render_textures.c \
	src_bonus/rendering/render_map.c \
	src_bonus/rendering/render_game.c \
	src_bonus/rendering/render_view.c \
	src_bonus/rendering/render_utils.c

# ==== OBJECT FILES ====
OBJ_DIR = obj
OBJ_BONUS_DIR = obj_bonus
OBJS = $(SRCS:%.c=$(OBJ_DIR)/%.o)
OBJS_BONUS = $(SRCS_BONUS:%.c=$(OBJ_BONUS_DIR)/%.o)

# ==== LIBS ====
LIBFT_DIR := Libft
LIBFT := $(LIBFT_DIR)/libft.a

MLX_DIR := ../minilibx-linux
MLX_FLAGS := -L$(MLX_DIR) -lmlx_Linux -lXext -lX11 -lm
LIBMLX := $(MLX_DIR)/libmlx.a

# ==== HEADER ====
CUB3D_H = includes/cub3d.h

# ==== RULES ====

all: $(OBJ_DIR) $(LIBFT) $(LIBMLX) $(NAME)

# Create obj/ directory
$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)/src \
	           $(OBJ_DIR)/src/parsing \
	           $(OBJ_DIR)/src/utils \
	           $(OBJ_DIR)/src/rendering

$(OBJ_BONUS_DIR):
	@mkdir -p $(OBJ_BONUS_DIR)/src_bonus \
	           $(OBJ_BONUS_DIR)/src_bonus/parsing \
	           $(OBJ_BONUS_DIR)/src_bonus/utils \
	           $(OBJ_BONUS_DIR)/src_bonus/rendering

$(LIBMLX):
	@echo "Building MiniLibX..."
	@make -s -C $(MLX_DIR) >/dev/null 2>&1;

$(LIBFT): 
	@echo "Building Libft..."
	@make -C $(LIBFT_DIR) -s

$(NAME): $(OBJS)
	@echo "Building $(NAME)..."
	$(CC) $(CFLAGS) $(INCLUDES) $(OBJS) -L$(LIBFT_DIR) -lft $(MLX_FLAGS) -o $(NAME)

# Compile normal .o files into obj/
$(OBJ_DIR)/%.o: %.c $(CUB3D_H)
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

# ==== BONUS ====

bonus: $(OBJ_BONUS_DIR) $(LIBFT) $(LIBMLX) $(OBJS_BONUS)
	@echo "Building $(NAME) with bonus..."
	$(CC) $(CFLAGS) $(INCLUDES) $(OBJS_BONUS) -L$(LIBFT_DIR) -lft $(MLX_FLAGS) -o $(NAME)

# Compile bonus .o files into obj_bonus/
$(OBJ_BONUS_DIR)/%.o: %.c $(CUB3D_H)
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

# ==== CLEANING ====

clean:
	@echo "Cleaning object files..."
	@rm -rf $(OBJ_DIR) $(OBJ_BONUS_DIR)
	@echo "Cleaning Libft..."
	@make -C $(LIBFT_DIR) clean
	@echo "Cleaning MiniLibX..."
	@make -C $(MLX_DIR) clean

fclean: clean
	@echo "Removing $(NAME)..."
	@rm -f $(NAME)
	@echo "Full cleaning Libft..."
	@make -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all bonus clean fclean re

