# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: slombard <slombard@student.42berlin.de>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/10/01 12:13:57 by slombard          #+#    #+#              #
#    Updated: 2023/10/12 19:10:15 by slombard         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo
# Detect the OS
UNAME_S := $(shell uname -s)
CC = cc
# If the OS is Darwin (macOS), set CC to gcc-13
ifeq ($(UNAME_S),Darwin)
    CC = gcc-13
endif
RM = rm -rf
CFLAGS = -Wall -Wextra -Werror -g -pthread
INCLUDES = -I./includes
OBJ_DIR = obj/
SRC_DIR = src/


SRC_FILES 	= philosophers.c init.c states.c forks.c utils.c utils_2.c

SRCS = $(addprefix $(SRC_DIR), $(SRC_FILES))
OBJS 	= $(addprefix $(OBJ_DIR), $(SRC_FILES:.c=.o))

all: $(OBJ_DIR) $(NAME) 
	@echo "Compiling with $(CC)"

$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	$(CC) $(CFLAGS) $(INCLUDES)  -c $< -o $@

$(OBJ_DIR):
	mkdir $(OBJ_DIR)

$(NAME): $(OBJS)
		$(CC) $(CFLAGS) $(INCLUDES) $(OBJS) -o $(NAME)
#		$(CC) $(CFLAGS) $(INCLUDES) -fsanitize=thread -lpthread $(OBJS) -o $(NAME) 

clean:
		$(RM) $(OBJ_DIR)
		

fclean: clean
		$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
