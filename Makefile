NAME = libftprintf.a
CC = cc 
FLAGS = -Wall -Wextra -Werror
AR = ar rcs
RM = rm -f 

SRC = lenstring.c lennumber.c lennumhex.c \
	printchar.c printstring.c printdecimal.c  printhex.c \
	printptr.c printuns.c ft_printf.c print_hash.c \

OBJ = $(SRC:.c=.o)

.PHONY : all clean fclean re

all : $(NAME)

$(NAME) : $(OBJ)
	$(AR) $(NAME) $?

%.o:%.c ft_printf.h
	$(CC) $(FLAGS) -c $< -o $@

clean :
	$(RM) $(OBJ)

fclean : clean
	$(RM) $(NAME)

re : fclean all