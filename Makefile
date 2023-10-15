CC = cc

NAME = philo
CFLAGS = -g -Wall -Wextra -Werror -pthread
INCLUDES = -I./includes
SRC_DIR = src
OBJ_DIR = obj

SRCS = philosophers.c utils.c prints.c check_input.c init.c start.c end.c forks.c check_routines.c single.c allocate.c routines.c

OBJS = $(addprefix $(OBJ_DIR)/, $(SRCS:.c=.o))

all: $(NAME)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(INCLUDES) $^ -o $@

clean:
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re
	