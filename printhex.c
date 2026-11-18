/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printhex.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slaarous <slaarous@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/28 17:36:06 by slaarous          #+#    #+#             */
/*   Updated: 2026/11/18 13:15:16 by slaarous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	print_lower_hex(unsigned long n)
{
	char	*hex;

	hex = "0123456789abcdef";
	if (n >= 16)
		print_lower_hex(n / 16);
	ft_putc(hex[n % 16]);
}

void	print_upper_hex(unsigned long n)
{
	char	*hex;	

	hex = "0123456789ABCDEF";
	if (n >= 16)
		print_upper_hex(n / 16);
	ft_putc(hex[n % 16]);
}

int	printhex(t_format *fmt, unsigned int x, int upper)
{
	int				count;
	unsigned long	n;
	n = x;
	count = lennumhex(n);
	if (fmt->hash)
	{
		if (n == 0)
			return (printdecimal(fmt, 0));
		count += ft_puts("0x");
		if (upper == 0)
			print_lower_hex(n);
		else
			print_upper_hex(n);
		return (count);
	}
	if (upper == 1)
		print_upper_hex(n);
	else if (upper == 0)
		print_lower_hex(n);
	else
		return (-1);
	return (count);
}
