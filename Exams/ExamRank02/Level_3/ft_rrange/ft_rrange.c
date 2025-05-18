/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_rrange.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erazumov <erazumov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 19:34:51 by erazumov          #+#    #+#             */
/*   Updated: 2025/05/13 22:12:30 by erazumov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

int	*ft_rrange(int start, int end)
{
	int	i;
	int	size;
	int	*rrange;

	if (start <= end)
		size = end - start + 1;
	else
		size = start - end + 1;
	rrange = (int *)malloc(sizeof(int) * size);
	if (!rrange)
		return (NULL);
	i = 0;
	while (i < size)
	{
		if (start <= end)
			rrange[i] = end - i;
		else
			rrange[i] = end + i;
		i++;
	}
	return (rrange);
}

/*
#include <stdio.h>

int	main(int ac, char **av)
{
	int	start = atoi(av[1]);
	int	end = atoi(av[2]);
	int	*arr = ft_rrange(start, end);
	
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