/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_append_utils.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erazumov <erazumov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 11:20:05 by erazumov          #+#    #+#             */
/*   Updated: 2025/08/18 10:46:34 by erazumov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* (Second pass helper) Appends a source string to a destination string
 * at a given index 'j'. */
size_t	append_str_to_result(char *dest, const char *src, size_t j)
{
	int	k;

	k = 0;
	while (src && src[k])
	{
		dest[j + k] = src[k];
		k++;
	}
	return (j + k);
}
