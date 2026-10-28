/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printuns.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slaarous <slaarous@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/28 17:26:54 by slaarous          #+#    #+#             */
/*   Updated: 2026/10/28 17:36:39 by slaarous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	printuns(long x)
{
	int	count;

	count = lennumber(x);
	if (x >= 10)
		printuns(x / 10);
	printchar((x % 10) + '0');
	return (count);
}
