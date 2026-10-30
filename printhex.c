/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printhex.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slaarous <slaarous@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/28 17:36:06 by slaarous          #+#    #+#             */
/*   Updated: 2026/10/28 18:22:29 by slaarous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	print_lower_hex(unsigned long n)
{
	char	*hex;

	hex = "0123456789abcdef";
	if (n >= 16)
		print_lower_hex(n / 16);
	printchar(hex[n % 16]);
}

void	print_upper_hex(unsigned long n)
{
	char	*hex;	

	hex = "0123456789ABCDEF";
	if (n >= 16)
		print_upper_hex(n / 16);
	printchar(hex[n % 16]);
}

int	printhex(unsigned int x, int upper)
{
	int				count;
	unsigned long	n;

	n = x;
	count = lennumhex(n);
	if (upper == 1)
		print_upper_hex(n);
	else if (upper == 0)
		print_lower_hex(n);
	else
		return (-1);
	return (count);
}
