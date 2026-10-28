#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <unistd.h>
# include <stdlib.h>

// print format :
int	printdecimal(long x);
int	printchar(char c);
int	printstring(char*s);
int	printuns(long x);
int	printhex(unsigned int n, int upper);

// count number :

unsigned int		lennumhex(unsigned int n);
int					lenstring(char *s);
int					lennumber(long n);

#endif