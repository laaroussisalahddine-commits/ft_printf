/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printuns.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slaarous <slaarous@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/28 17:26:54 by slaarous          #+#    #+#             */
/*   Updated: 2026/11/18 13:39:31 by slaarous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	printuns(t_format *fmt, unsigned int n)
{
	int		count;
	long	x;

	x = n;
	count = lennumber(x);
	if (x >= 10)
		printuns(fmt, x / 10);
	ft_putc((x % 10) + '0');
	return (count);
}
