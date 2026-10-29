/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lennumber.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slaarous <slaarous@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/28 17:26:08 by slaarous          #+#    #+#             */
/*   Updated: 2026/10/29 19:36:53 by slaarous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	lennumber(long n)
{
	int	count;

	count = 1;
	if (n < 0)
	{
		count++;
		n = -n;
	}
	while (n >= 10)
	{
		count++;
		n = n / 10;
	}
	return (count);
}
