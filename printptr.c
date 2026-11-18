/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printptr.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slaarous <slaarous@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/28 17:25:52 by slaarous          #+#    #+#             */
/*   Updated: 2026/11/18 12:56:49 by slaarous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	printptr(t_format *fmt, void *ptr)
{
	int		count;
	long	a;

	a = (long)ptr;
	count = lennumhex(a);
	if (!ptr)
	{
		printstring(fmt, "(nil)");
		return (5);
	}
	count += printstring(fmt, "0x");
	print_lower_hex(a);
	return (count);
}
