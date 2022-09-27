FLAGS=-Wall -Wextra -Werror -O3

SRC=errors.c free.c ft_ls.c list_long.c list_sort.c list.c print.c print2.c \
	recursion.c utilities.c utilities2.c

LS_DIR=srcs/
BIN_NAME=ft_ls
PRINTF_LIB=printf/libftprintf.a
FULL_SRC=$(addprefix $(LS_DIR), $(SRC))
OBJ_FULL=$(addprefix $(LS_DIR), $(SRC:%.c=%.o))

all: $(BIN_NAME)

$(BIN_NAME): $(FULL_SRC:%.c=%.o)
	gcc $(FLAGS) -o $(BIN_NAME) $(OBJ_FULL) $(PRINTF_LIB)

%.o: %.c $(PRINTF_LIB)
	gcc $(FLAGS) -c $(<) -o $(@)

$(PRINTF_LIB):
	$(MAKE) -C printf/

clean:
	$(MAKE) -C printf/ clean
	rm -f $(OBJ_FULL)

fclean: clean
	$(MAKE) -C printf/ fclean
	rm -f $(BIN_NAME)

re: fclean all

.PHONY: all clean fclean re
