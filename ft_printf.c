/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slaarous <slaarous@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/28 18:42:17 by slaarous          #+#    #+#             */
/*   Updated: 2026/10/28 20:40:05 by slaarous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int ft_printf(const char *str, ...)
{
    va_list args;
    int     i;
    int     count;

    va_start(args, str);
    i = 0;
    count = 0;
    while (str[i])
    {
        if (str[i] == '%')
        {
            if (str[i + 1] == 'c')
            {
                count += printchar(va_arg(args, int));
                i += 2;
            }
            else if (str[i + 1] == 's')
            {
                count += printstring(va_arg(args, char *));
                i += 2;
            }
            else if (str[i + 1] == 'd' || str[i + 1] == 'i' )
            {
                count += printdecimal(va_arg(args, long));
                i += 2;
            }
            else if (str[i + 1] == 'x')
            {
                count += printhex(va_arg(args, unsigned long), 0);
                i += 2;
            }
            else if (str[i + 1] == 'X')
            {
                count += printhex(va_arg(args, unsigned long), 1);
                i += 2;
            }
            else if (str[i + 1] == 'p')
            {
                count += printptr(va_arg(args, void *));
                i += 2;
            }
            else if (str[i + 1] == 'u')
            {
                count += printuns(va_arg(args, unsigned int));
                i += 2;
            }
            else if (str[i + 1] == '%')
            {
                count += printchar('%');
                i += 2;
            }
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
