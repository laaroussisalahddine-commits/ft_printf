NAME = libftprintf.a
CC = cc 
FLAGS = -Wall -Wextra -Werror
AR = ar rcs
RM = rm -f 

SRC = lenstring.c lennumber.c lennumhex.c \
	printchar.c printstring.c printdecimal.c  printhex.c \
	printptr.c printuns.c ft_printf.c utils.c\

OBJ = $(SRC:.c=.o)

.PHONY : all clean fclean re

run : re
	$(CC) $(FLAGS) main.c libftprintf.a
	@$(MAKE) --no-print-directory -s clean

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