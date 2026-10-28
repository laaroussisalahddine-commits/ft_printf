#include "ft_printf.h"

void	print_lower_hex(unsigned int n)
{
	char	*hex;

	hex = "0123456789abcdef";
	if (n >= 16)
		print_upper_hex(n / 16);
	printchar(hex[n % 16]);
}

void	print_upper_hex(unsigned int n)
{
	char	*hex;	

	hex = "0123456789ABCDEF";
	if (n >= 16)
		print_upper_hex(n / 16);
	printchar(hex[n % 16]);
}

int	printhex(unsigned int n, int upper)
{
	int	count;

	count = lennumhex(n);
	if (upper == 1)
		print_upper_hex(n);
	else if (upper == 0)
		print_lower_hex(n);
	return (count);
}
