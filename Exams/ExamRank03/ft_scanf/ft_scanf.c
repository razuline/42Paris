/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_scanf.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erazumov <erazumov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 19:54:19 by erazumov          #+#    #+#             */
/*   Updated: 2025/07/23 12:50:00 by erazumov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdarg.h>
#include <stdio.h>
#include <ctype.h>

// Consomme les espaces blancs de l'entrée
static int	match_space(FILE *f)
{
	int	c;

	while ((c = fgetc(f)) != EOF && isspace(c))
		;
	if (c != EOF)
		ungetc(c, f);
	return (0);
}

// Vérifie si le prochain caractère correspond à 'c'
static int	match_char(FILE *f, char c)
{
	int	next_c = fgetc(f);

	if (next_c == (int)c)
		return (1);
	if (next_c != EOF)
		ungetc(next_c, f);
	return (0);
}

// Gère la conversion %c
static int	scan_char(FILE *f, va_list ap)
{
	char	*dest = va_arg(ap, char *);
	int		c = fgetc(f);

	if (c == EOF)
		return (0);
	*dest = (char)c;
	return (1);
}

// Gère la conversion %d
static int	scan_int(FILE *f, va_list ap)
{
	int			*dest = va_arg(ap, int *);
	int			c;
	int			sign = 1;
	long long	result = 0;
	int			found = 0;

	c = fgetc(f);
	if (c == '-')
		sign = -1;
	else if (c == '+')
		sign = 1;
	else
		ungetc(c, f);
	while ((c = fgetc(f)) != EOF && isdigit(c))
	{
		result = result * 10 + (c - '0');
		found = 1;
	}
	if (c != EOF)
		ungetc(c, f);
	if (found)
	{
		*dest = (int)(result * sign);
		return (1);
	}
	return (0);
}

// Gère la conversion %s
static int	scan_string(FILE *f, va_list ap)
{
	char	*dest = va_arg(ap, char *);
	int		c;
	int		found = 0;

	while ((c = fgetc(f)) != EOF && !isspace(c))
	{
		*dest++ = (char)c;
		found = 1;
	}
	if (c != EOF)
		ungetc(c, f);
	*dest = '\0';
	return (found);
}

/*
int	match_conv(FILE *f, const char **format, va_list ap)
{
	switch (**format)
	{
		case 'c':
			return scan_char(f, ap);
		case 'd':
			match_space(f);
			return scan_int(f, ap);
		case 's':
			match_space(f);
			return scan_string(f, ap);
		case EOF:
			return -1;
		default:
			return -1;
	}
}

int	ft_vfscanf(FILE *f, const char *format, va_list ap)
{
	int nconv = 0;

	int c = fgetc(f);
	if (c == EOF)
		return EOF;
	ungetc(c, f);

	while (*format)
	{
		if (*format == '%')
		{
			format++;
			if (match_conv(f, &format, ap) != 1)
				break;
			else
				nconv++;
		}
		else if (isspace(*format))
		{
			if (match_space(f) == -1)
				break;
		}
		else if (match_char(f, *format) != 1)
			break;
		format++;
	}
	
	if (ferror(f))
		return EOF;
	return nconv;
}
*/

int	ft_scanf(const char *format, ...)
{
	va_list	ap;
	int		ret;

	va_start(ap, format);
	ret = ft_vfscanf(stdin, format, ap);
	va_end(ap);
	return (ret);
}
