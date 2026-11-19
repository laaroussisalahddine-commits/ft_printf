/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slaarous <slaarous@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/19 16:45:34 by slaarous          #+#    #+#             */
/*   Updated: 2026/11/19 16:45:41 by slaarous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	initial_format(t_format *fmt)
{
	fmt->hash = 0;
	fmt->plus = 0;
	fmt->spaces = 0;
	fmt->specifier = '\0';
}

int	is_specifier(char s)
{
	return (s == 'c' || s == 's' || s == 'd'
		|| s == 'i' || s == 'u' || s == 'p'
		|| s == 'x' || s == 'X' || s == '%');
}

int	is_flags(char c)
{
	return (c == '#' || c == '+'
		||c == ' ' );
}
