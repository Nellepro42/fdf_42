# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: neprocur <neprocur@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2015/10/30 09:59:11 by neprocur          #+#    #+#              #
#    Updated: 2015/10/30 09:59:15 by neprocur         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= fdf
DEBUG		= debug_version_$(NAME)
LIBFT_DIR	= libft
LIBFT		= $(LIBFT_DIR)/libft.a
MINILIBX_DIR= minilibx_macos
MINILIBX	= $(MINILIBX_DIR)/libmlx.a
CC			= gcc
LFLAGS		= -L ./libft -lft -L ./minilibx_macos -lmlx -framework OpenGL -framework AppKit
CFLAGS		= -Wall -Wextra -Werror
IFLAGS		= -I ./libft/ -I ./minilibx_macos/ -I./
DFLAGS		= -g -DD_ERROR_ON
RM			= rm -Rf

H			= 	fdf.h
SRC			= 	fdf.c \
				draw_line.c \
				key_hook.c \
				hook.c

OBJ			= $(SRC:.c=.o)

$(NAME): $(MINILIBX) $(LIBFT) $(OBJ) $(H)
	@echo "building $(NAME) ... "
	@$(CC) $(CFLAGS) -o $@ $(OBJ) $(IFLAGS) $(LFLAGS)
	@echo "$(NAME) created ! \n"
	@echo "building $(DEBUG) ... "
	@$(CC) $(CFLAGS) $(DFLAGS) $(SRC) -o $(DEBUG) $(IFLAGS) $(LFLAGS)
	@echo "$(DEBUG) created !"

%.o: %.c
	@$(CC) $(CFLAGS) $(IFLAGS) -c $^ -o $@

$(LIBFT):
	@echo "building $(LIBFT_DIR) ... "
	@($(MAKE) -C ./$(LIBFT_DIR))
	@echo "$(LIBFT_DIR) created ! \n"

$(MINILIBX):
	@echo "building $(MINILIBX_DIR) ... "
	@($(MAKE) -C ./$(MINILIBX_DIR))
	@echo "$(MINILIBX_DIR) created ! \n"

all:$(NAME)

clean:
	@$(RM) $(DEBUG) $(DEBUG).dSYM $(OBJ)
	@(cd  $(LIBFT_DIR) && $(MAKE) $@)
	@(cd  $(MINILIBX_DIR) && $(MAKE) $@)
	@echo "$(DEBUG), $(DEBUG).dSYM, objects erased !"

fclean:clean
	@$(RM) $(NAME)
	@(cd  $(LIBFT_DIR) && $(MAKE) $@)
	@echo "$(NAME), $(LIBFT_DIR) erased !\n"

re: fclean all

.PHONY:all clean fclean re
