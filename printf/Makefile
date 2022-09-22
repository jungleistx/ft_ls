FLAGS=-Wall -Wextra -Werror -O3

SRC=address.c assign.c bonus.c char.c flags.c \
	flags2.c float.c ft_printf.c helpers.c \
	hex_flags.c hex.c int_flags.c int.c octal_flags.c \
	octal.c percent.c string.c unsigned.c
SRC_DIR=srcs/

LIBFT_SRC=ft_atoi.c ft_bzero.c ft_isdigit.c ft_memdel.c ft_memset.c \
	ft_putchar.c ft_putstr_fd.c ft_strcat.c ft_strchr.c ft_strcmp.c \
	ft_strcpy.c ft_strdup.c ft_strlen.c ft_strncpy.c ft_itoa.c
LIBFT_DIR=libft/

LIB_NAME=libftprintf.a

all : $(LIB_NAME)

$(LIB_NAME) :
	gcc ${FLAGS} -c $(addprefix $(SRC_DIR), $(SRC)) \
	$(addprefix $(LIBFT_DIR), $(LIBFT_SRC))	-I ./includes/ -I ./libft/
	ar rc ${LIB_NAME} $(SRC:.c=.o) $(LIBFT_SRC:.c=.o)

clean:
	rm -f $(SRC:.c=.o) $(LIBFT_SRC:.c=.o)

fclean:	clean
	rm -f ${LIB_NAME}

re: fclean all

.PHONY: all clean fclean re
