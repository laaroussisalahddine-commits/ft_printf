#include "ft_printf.h"

int	lennumber(long n)
{
	int	count;

	count = 1;
	if (n < 0)
		count++;
	while (n >= 10)
	{
		count++;
		n = n / 10;
	}
	return (count);
}
