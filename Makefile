NAME = ft_printf.a
CC = cc 
FLAGS = -Wall -Wextra -Werror
AR = ar rcs
RM = rm -f 

SRC = lenstring.c printchar.c printstring.c

OBJ = $(FILES:.c=.o)

.PHONY all clean fclean re

all : $(NAME)

$(NAME) : $(OBJ)

%.o:%.c ft_printf.h
	$(CC) $(FLAGS) -c $< -o $@

clean :
	$(RM) $(OBJ)

fclean : clean
	$(RM) $(NAME)

re : fclean all