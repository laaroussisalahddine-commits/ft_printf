/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printstring.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slaarous <slaarous@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/28 17:26:50 by slaarous          #+#    #+#             */
/*   Updated: 2026/11/18 13:10:00 by slaarous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_puts(char *s)
{
	int	i;

	i = 0;
	while (s[i])
		ft_putc(s[i++]);
	return (lenstring(s));
}

int	printstring(t_format *fmt, char*s)
{
	int	i;
	if (!s)
	{
		write (1, "(null)\n", 6);
		return (6);
	}
	i = 0;
	if (fmt->width == lenstring(s))
		return (ft_puts(s));
	while (s[i])
		write(1, &s[i++], 1);
	return (lenstring(s));
}
