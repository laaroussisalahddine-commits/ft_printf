/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lennumhex.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slaarous <slaarous@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/28 17:26:11 by slaarous          #+#    #+#             */
/*   Updated: 2026/10/28 17:36:30 by slaarous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

unsigned int	lennumhex(unsigned int n)
{
	int	count;

	count = 1;
	while (n >= 16)
	{
		count++;
		n = n / 16;
	}
	return (count);
}
