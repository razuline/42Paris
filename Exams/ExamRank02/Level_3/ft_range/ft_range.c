/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_range.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erazumov <erazumov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 19:12:34 by erazumov          #+#    #+#             */
/*   Updated: 2025/05/13 22:12:25 by erazumov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

int	*ft_range(int start, int end)
{
	int	i;
	int	size;
	int	*range;

	if (start <= end)
		size = end - start + 1;
	else
		size = start - end + 1;
	range = (int *)malloc(sizeof(int) * size);
	if (!range)
		return (NULL);
	i = 0;
	while (i < size)
	{
		if (start <= end)
			range[i] = start + i;
		else
			range[i] = start - i;
		i++;
	}
	return (range);
}

/*
#include <stdio.h>

int	main(int ac, char **av)
{
	int	start = atoi(av[1]);
	int	end = atoi(av[2]);
	int	*arr = ft_range(start, end);
	
	if (ac != 3)
	{
		printf("\n");
		return (0);
	}
	for (int i = 0; i < (abs(end - start) + 1); i++)
		printf("%d ", arr[i]);
	printf("\n");
	free(arr);
	return (0);
}
*/