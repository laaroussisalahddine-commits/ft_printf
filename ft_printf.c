/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slaarous <slaarous@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/28 18:42:17 by slaarous          #+#    #+#             */
/*   Updated: 2026/10/29 16:28:23 by slaarous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	format(char str, va_list args)
{
	int	count;

	count = 0;
	if (str == 'c')
		count += printchar(va_arg(args, int));
	else if (str == 's')
		count += printstring(va_arg(args, char *));
	else if (str == 'd' || str == 'i' )
		count += printdecimal(va_arg(args, int));
	else if (str == 'x')
		count += printhex(va_arg(args, unsigned long), 0);
	else if (str == 'X')
		count += printhex(va_arg(args, unsigned long), 1);
	else if (str == 'p')
		count += printptr(va_arg(args, void *));
	else if (str == 'u')
		count += printuns(va_arg(args, unsigned int));
	else if (str == '%')
		count += printchar('%');
	return (count);
}

int	ft_printf(const char *str, ...)
{
	va_list	args;
	int		i;
	int		count;

	va_start(args, str);
	i = 0;
	count = 0;
	while (str[i])
	{
		if (str[i] == '%')
		{
			count += format (str[i + 1], args);
			i += 2;
		}
		else
		{
			count += printchar(str[i]);
			i++;
		}
	}
	va_end(args);
	return (count);
}
