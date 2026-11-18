/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printdecimal.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slaarous <slaarous@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/28 17:26:38 by slaarous          #+#    #+#             */
/*   Updated: 2026/11/18 13:12:33 by slaarous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_putlong(long n)
{
	if (n >= 10)
		ft_putlong(n / 10);
	ft_putc((n % 10) + '0');
}

int	printdecimal(t_format *fmt, int x)
{
	long	n;
	int		count;
	int		skip;
	int		len_number = 1;

	n = x;
	count = lennumber(n);
	if (!fmt->spaces)
	{
		skip = fmt-> width - len_number;
		ft_strset(skip, ' ');
		printdecimal(fmt, n);
	} // error;
	if (n < 0)
	{
		ft_putc('-');
		n = -n;
	}
	ft_putlong(n);
	return (count);
}
