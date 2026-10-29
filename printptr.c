/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printptr.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slaarous <slaarous@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/28 17:25:52 by slaarous          #+#    #+#             */
/*   Updated: 2026/10/29 16:33:54 by slaarous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	printptr(void *ptr)
{
	int		count;
	long	a;

	a = (long)ptr;
	count = lennumhex(a);
	if (!ptr)
	{
		printstring("0x0");
		return (3);
	}
	count += printstring("0x");
	printhex(a, 0);
	return (count);
}
