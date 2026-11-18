#include "ft_printf.h"

void	initial_format(t_format *fmt)
{
	fmt->hash = 0;
	fmt->plus = 0;
	fmt->spaces = 0;
	fmt->width = 0;
	fmt->specifier = '\0';
}

void	ft_strset(int len, char c)
{
	while (len-- > 0)
		write(1, &c, 1);
}

int	is_specifier(char s)
{
	return (s == 'c' || s == 's' || s == 'd'
		|| s == 'i' || s == 'u' || s == 'p'
		|| s == 'x' || s == 'X' || s == '%');
}

int	is_flags(char c)
{
	return (c == '-' || c == '0'
		||c == '#' || c == '+'
		||c == ' ' );
}

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}
