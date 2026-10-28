#include "ft_printf.h"

int	printdecimal(long x)
{
	int	count;

	count = lennumber(x);
	if (x < 0)
	{
		printchar('-');
		x = -x;
	}
	if (x >= 10)
		printdecimal(x / 10);
	printchar((x % 10) + '0');
	return (count);
}
