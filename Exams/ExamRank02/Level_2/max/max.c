/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   max.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erazumov <erazumov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 18:29:26 by erazumov          #+#    #+#             */
/*   Updated: 2025/05/13 21:16:09 by erazumov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	max(int *tab, unsigned int len)
{
	int				curr_max;
	unsigned int	i;

	if (len == 0)
		return (0);
	curr_max = tab[0];
	i = 1;
	while (i < len)
	{
		if (tab[i] > curr_max)
			curr_max = tab[i];
		i++;
	}
	return (curr_max);
}

/*
#include <stdio.h>

int	main(void)
{
	int arr1[] = {1, 5, 3, 9, 2};
	int arr2[] = {-5, -3, -9, -1};
	int arr3[] = {42};
	int arr4[] = {0};
	int *arr5 = NULL;
	
	printf("Test1: %d (expect 9)\n", max(arr1, 5));
	printf("Test2: %d (expect -1)\n", max(arr2, 4));
	printf("Test3: %d (expect 42)\n", max(arr3, 1));
	printf("Test4: %d (expect 0)\n", max(arr4, 1));
	printf("Test5: %d (expect 0)\n", max(arr5, 0));
	
	return (0);
}
*/