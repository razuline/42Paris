/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erazumov <erazumov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/10 14:56:38 by erazumov          #+#    #+#             */
/*   Updated: 2025/08/10 14:57:22 by erazumov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @brief Compare deux chaînes de caractères lexicographiquement.
 *
 * @param s1 La première chaîne à comparer.
 * @param s2 La deuxième chaîne à comparer.
 * @return Un entier inférieur, égal ou supérieur à zéro si s1 est trouvée,
 * respectivement, plus petite, égale ou plus grande que s2.
 */

#include "libft.h"

int	ft_strcmp(const char *s1, const char *s2)
{
	size_t	i;

	i = 0;
	while (s1[i] && s2[i] && s1[i] == s2[i])
	{
		i++;
	}
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}
