/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erazumov <erazumov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 13:05:16 by erazumov          #+#    #+#             */
/*   Updated: 2025/05/27 13:44:53 by erazumov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdarg.h>
#include <stdlib.h>
#include <unistd.h>

void	ft_putstr(char *s, int *count)
{
	int	i;

	if (!s)
		s = "(null)";
	i = 0;
	while (s[i])
	{
		write(1, &s[i], 1);
		i++;
		(*count)++;
	}
}

void	ft_putnbr(int n, int *count)
{
	char	c;

	if (n == -2147483648)
	{
		ft_putstr("-2147483648", count);
		return ;
	}
	if (n < 0)
	{
		write(1, "-", 1);
		(*count)++;
		n = -n;
	}
	if (n >= 10)
		ft_putnbr(n / 10, count);
	c = (n % 10) + '0';
	write(1, &c, 1);
	(*count)++;
}

void	ft_puthex(unsigned int n, int *count)
{
	char	*hex = "0123456789abcdef";

	if (n >= 16)
		ft_puthex(n / 16, count);
	write(1, &hex[n % 16], 1);
	(*count)++;
}

int	ft_printf(const char *format, ...)
{
	int		i;
	int		count;
	va_list	args;

	if (!format)
		return (-1);

	i = 0;
	count = 0;
	va_start(args, format);

	while (format[i])
	{
		if (format[i] == '%' && format[i + 1])
		{
			i++;
			if (format[i] == 's')
				ft_putstr(va_arg(args, char *), &count);
			else if (format[i] == 'd')
				ft_putnbr(va_arg(args, int), &count);
			else if (format[i] == 'x')
				ft_puthex(va_arg(args, unsigned int), &count);
			else
			{
				write(1, &format[i], 1);
				count++;
			}
		}
		else
		{
			write(1, &format[i], 1);
			count++;
		}
		i++;
	}
	va_end(args);
	return (count);
}

/*
#include <stdio.h>
#include <limits.h>

int	main(void)
{
	int	count;
	int	real_count;

	printf("=== Basic Tests ===\n");

	// Test 1: Simple string
	count = ft_printf("1. String: %s\n", "Hello");
	real_count = printf("1. String: %s\n", "Hello");
	printf("ft_printf: %d chars, printf: %d chars\n\n", count, real_count);

	// Test 2: Integer
	count = ft_printf("2. Decimal: %d\n", 42);
	real_count = printf("2. Decimal: %d\n", 42);
	printf("ft_printf: %d chars, printf: %d chars\n\n", count, real_count);

	// Test 3: Hexadecimal
	count = ft_printf("3. Hexadecimal: %x\n", 255);
	real_count = printf("3. Hexadecimal: %x\n", 255);
	printf("ft_printf: %d chars, printf: %d chars\n\n", count, real_count);

	printf("=== Edge Cases ===\n");

	// Test 4: Empty string
	count = ft_printf("4. Empty: %s\n", "");
	real_count = printf("4. Empty: %s\n", "");
	printf("ft_printf: %d chars, printf: %d chars\n\n", count, real_count);

	// Test 5: NULL string - fixed by casting NULL to char*
	count = ft_printf("5. NULL: %s\n", (char *)NULL);
	real_count = printf("5. NULL: %s\n", (char *)NULL);
	printf("ft_printf: %d chars, printf: %d chars\n\n", count, real_count);

	// Test 6: INT_MIN
	count = ft_printf("6. INT_MIN: %d\n", INT_MIN);
	real_count = printf("6. INT_MIN: %d\n", INT_MIN);
	printf("ft_printf: %d chars, printf: %d chars\n\n", count, real_count);

	// Test 7: Multiple formats
	count = ft_printf("7. Mixed: %s %d %x\n", "Value:", 42, 42);
	real_count = printf("7. Mixed: %s %d %x\n", "Value:", 42, 42);
	printf("ft_printf: %d chars, printf: %d chars\n\n", count, real_count);

	printf("=== Formatting Tests ===\n");

	// Test 8: No format specifiers
	count = ft_printf("8. Just text\n");
	real_count = printf("8. Just text\n");
	printf("ft_printf: %d chars, printf: %d chars\n\n", count, real_count);

	// Test 9: Literal %
	count = ft_printf("9. Percent sign: %%\n");
	real_count = printf("9. Percent sign: %%\n");
	printf("ft_printf: %d chars, printf: %d chars\n\n", count, real_count);

	return (0);
}
*/
