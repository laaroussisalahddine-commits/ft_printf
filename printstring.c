/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printstring.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slaarous <slaarous@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/28 17:26:50 by slaarous          #+#    #+#             */
/*   Updated: 2026/10/29 16:11:23 by slaarous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	printstring(char*s)
{
	int	i;

	if (!s)
	{
		write (1, "(null)\n", 6);
		return (6);
	}
	i = 0;
	while (s[i])
		write(1, &s[i++], 1);
	return (lenstring(s));
}
