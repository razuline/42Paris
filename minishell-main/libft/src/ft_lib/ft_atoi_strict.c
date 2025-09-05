/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_strict.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: preltien <preltien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 15:03:15 by preltien          #+#    #+#             */
/*   Updated: 2025/08/05 15:32:02 by preltien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <limits.h>

int	ft_atoi_strict(const char *str, int *error)
{
	long	num;
	int		sign;

	*error = 0;
	num = 0;
	sign = 1;
	while (ft_isspace(*str))
		str++;
	if (*str == '+' || *str == '-')
		if (*str++ == '-')
			sign = -1;
	if (!ft_isdigit(*str))
		return (*error = 1, 0);
	while (ft_isdigit(*str))
	{
		num = num * 10 + (*str++ - '0');
		if ((sign == 1 && num > INT_MAX) || (sign == -1 && (-num) < INT_MIN))
			return (*error = 1, 0);
	}
	if (*str != '\0')
		return (*error = 1, 0);
	return ((int)(num * sign));
}
