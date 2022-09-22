FLAGS=-Wall -Wextra -Werror -O3

SRC=errors.c free.c ft_ls.c list_long.c list_sort.c list.c print.c print2.c \
	recursion.c utilities.c utilities2.c

LS_DIR=srcs/

BIN_NAME=ft_ls

PRINTF_LIB=printf/libftprintf.a

all : objects
	gcc $(FLAGS) -o $(BIN_NAME) $(SRC:.c=.o) $(PRINTF_LIB)

objects : $(PRINTF_LIB)
	gcc $(FLAGS) -c $(addprefix $(LS_DIR), $(SRC))

$(PRINTF_LIB) :
	$(MAKE) -C printf/

clean :
	$(MAKE) -C printf/ clean
	rm -f $(SRC:.c=.o)

fclean : clean
	$(MAKE) -C printf/ fclean
	rm -f $(BIN_NAME)

re : fclean all

.PHONY: all clean fclean re
