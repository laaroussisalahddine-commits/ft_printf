#include "ft_printf.h"

unsigned int	lennumhex(unsigned int n)
{
	int	count;

	count = 1;
	while (n >= 16)
	{
		count++;
		n = n / 16;
	}
	return (count);
}
