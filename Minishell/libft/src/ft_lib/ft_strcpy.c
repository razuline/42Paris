/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erazumov <erazumov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/15 14:10:18 by erazumov          #+#    #+#             */
/*   Updated: 2025/08/17 17:48:22 by erazumov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
 * @brief Copies the string pointed to by src, including the terminating
 * null byte ('\0'), to the buffer pointed to by dest.
 *
 * @param dest Pointer to the dest array where the content is to be copied.
 * @param src  The string to be copied.
 * @return A pointer to the destination string dest.
 */

#include "libft.h"

char	*ft_strcpy(char *dest, const char *src)
{
	int	i;

	i = 0;
	while (src[i] != '\0')
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}
