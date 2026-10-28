#include "ft_printf.h"

int	printuns(long x)
{
	int	count;

	count = lennumber(x);
	if (x >= 10)
		printuns(x / 10);
	printchar((x % 10) + '0');
	return (count);
}
