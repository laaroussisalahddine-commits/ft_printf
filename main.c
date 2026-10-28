#include "ft_printf.h"

int main(void)
{
    int res;
    int a = 42;

    res = ft_printf("char = %c \nstr = %s \nint = %d \nhex = %X \n%% \nptr = %p", 'A', "Hello", 1337, 42, &a);
    
    ft_printf("\n\ncount of caracter : %d\n",res);
    return(0);
}