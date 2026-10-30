/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_hash.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slaarous <slaarous@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/30 17:26:08 by slaarous          #+#    #+#             */
/*   Updated: 2026/10/30 19:38:44 by slaarous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	print_hash(unsigned long n , int upper)
{
	int	count;

	count = lennumhex(n);
	if (n == 0)
	{
		printdecimal(0);
		return (1);
	}
	count += printstring("0x");
	printhex(n, upper);
	return (count);	
}