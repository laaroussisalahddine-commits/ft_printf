/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printdecimal.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slaarous <slaarous@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/28 17:26:38 by slaarous          #+#    #+#             */
/*   Updated: 2026/11/19 16:43:46 by slaarous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_putnbr(long n)
{
	int	count;

	count = lennumber(n);
	if (n < 0)
	{
		printchar('-');
		n = -n;
	}
	if (n >= 10)
		ft_putnbr(n / 10);
	printchar((n % 10) + '0');
	return (count);
}

int	handle_flags(t_format *fmt, long n)
{
	int		count;

	count = lennumber(n);
	if (n >= 0)
	{
		if (fmt->spaces && !fmt->plus)
			count += printchar(' ');
		if ((fmt->plus && !fmt->spaces)
			|| (fmt->spaces && fmt->plus))
			count += printchar('+');
		ft_putnbr(n);
	}
	else
		ft_putnbr(n);
	return (count);
}

int	printdecimal(t_format *fmt, int x)
{
	long	n;

	n = x;
	if (fmt->plus || fmt->spaces)
		return (handle_flags(fmt, n));
	else
		return (ft_putnbr(n));
	return (-1);
}
