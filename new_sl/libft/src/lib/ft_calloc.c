/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erazumov <erazumov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/09 18:20:10 by erazumov          #+#    #+#             */
/*   Updated: 2024/11/26 15:03:49 by erazumov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* The calloc() function allocates memory for an array of nmemb elements
of size bytes each and returns a pointer to the allocated memory. The memory
is set to zero. If nmemb or size is 0, then calloc() returns either NULL,
or a unique pointer value that can later be successfully passed to free().
If the multiplication of nmemb and size would result in integer overflow,
then calloc() returns an error.
By contrast, an integer overflow would not be detected in the following call
to malloc(), with the result that an incorrectly sized block of memory would
be allocated: malloc(nmemb * size); 
The calloc() function returns a pointer to the allocated memory, which is
suitably aligned for any built-in type. On error, this function returns NULL.
NULL may also be returned by a successful call to calloc() with nmemb
or size equal to zero. */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*result;

	result = malloc(nmemb * size);
	if (!result)
		return (0);
	ft_bzero(result, nmemb * size);
	return (result);
}
