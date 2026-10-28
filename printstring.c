#include "ft_printf.h"

int	printstring(char*s)
{
	int	i;

	if (!s)
		return (0);
	i = 0;
	while (s[i])
		write(1, &s[i++], 1);
	return (lenstring(s));
}
