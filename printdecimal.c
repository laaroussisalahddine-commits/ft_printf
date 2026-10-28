/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printdecimal.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slaarous <slaarous@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/28 17:26:38 by slaarous          #+#    #+#             */
/*   Updated: 2026/10/28 17:36:34 by slaarous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	printdecimal(long x)
{
	int	count;

	count = lennumber(x);
	if (x < 0)
	{
		printchar('-');
		x = -x;
	}
	if (x >= 10)
		printdecimal(x / 10);
	printchar((x % 10) + '0');
	return (count);
}
