/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printdecimal.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slaarous <slaarous@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/28 17:26:38 by slaarous          #+#    #+#             */
/*   Updated: 2026/10/29 16:33:12 by slaarous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_putlong(long n)
{
	if (n >= 10)
		ft_putlong(n / 10);
	printchar((n % 10) + '0');
}

int	printdecimal(int x)
{
	long	n;
	int		count;

	n = x;
	count = lennumber(n);
	if (n < 0)
	{
		printchar('-');
		n = -n;
	}
	ft_putlong(n);
	return (count);
}
