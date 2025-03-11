/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_formats.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erazumov <erazumov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 21:03:22 by erazumov          #+#    #+#             */
/*   Updated: 2024/12/03 14:48:44 by erazumov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_formats(va_list args, const char format)
{
	int	print_len;

	print_len = 0;
	if (format == '%')
		print_len += ft_printchar('%');
	else if (format == 'c')
		print_len += ft_printchar(va_arg(args, int));
	else if (format == 's')
		print_len += ft_printstr(va_arg(args, char *));
	else if (format == 'p')
		print_len += ft_printptr(va_arg(args, unsigned long long));
	else if (format == 'd' || format == 'i')
		print_len += ft_printnbr(va_arg(args, int));
	else if (format == 'u')
		print_len += ft_print_u(va_arg(args, unsigned int));
	else if (format == 'x' || format == 'X')
		print_len += ft_printhex(va_arg(args, unsigned int), format);
	return (print_len);
}
