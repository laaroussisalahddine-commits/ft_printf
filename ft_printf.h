/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slaarous <slaarous@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/28 17:26:04 by slaarous          #+#    #+#             */
/*   Updated: 2026/11/18 13:42:31 by slaarous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <stdarg.h>

typedef struct s_format
{
	int		hash;
	int		plus;
	int		spaces;
	int		width;
	char	specifier;
}		t_format;

/* print format */
int				printdecimal(t_format *fmt, int x);
int				printchar( char c);
int				printstring(t_format *fmt, char *s);
int				printuns(t_format *fmt, unsigned int n);
int				printhex(t_format *fmt, unsigned int n, int upper);
int				printptr(t_format *fmt, void *ptr);

/* count number */
unsigned int	lennumhex(unsigned long n);
int				lenstring(char *s);
int				lennumber(long n);

/* main function */
int				ft_printf(const char *str, ...);
int				print_format(va_list args, t_format *fmt);
void			parse_format(const char *str, int *i, t_format *fmt);
void			flags(const char *str, int *i, t_format *fmt);

/* helper */
void			initial_format(t_format *fmt);
void			ft_strset(int len, char c);
int				is_specifier(char s);
int				is_flags(char c);
int				ft_isdigit(int c);
void			print_lower_hex(unsigned long n);
int				ft_putc(char c);
int				ft_puts(char *s);

#endif