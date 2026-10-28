/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slaarous <slaarous@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/28 17:26:04 by slaarous          #+#    #+#             */
/*   Updated: 2026/10/28 18:46:45 by slaarous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <unistd.h>
# include <stdlib.h>
# include <stdarg.h>

// print format :
int	printdecimal(long x);
int	printchar(char c);
int	printstring(char*s);
int	printuns(long x);
int	printhex(unsigned long n, int upper);
int	printptr(void *ptr);

// count number :

unsigned int		lennumhex(unsigned int n);
int					lenstring(char *s);
int					lennumber(long n);

// main_function:
int ft_printf(const char *str, ...);

#endif