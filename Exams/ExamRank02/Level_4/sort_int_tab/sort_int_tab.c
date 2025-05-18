/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_int_tab.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erazumov <erazumov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 17:09:39 by erazumov          #+#    #+#             */
/*   Updated: 2025/05/13 22:15:06 by erazumov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

void	sort_int_tab(int *tab, unsigned int size)
{
	unsigned int	i;
	unsigned int	j;
	int				tmp;

	if (!tab || size < 2)
		return ;

	i = 0;
	while (i < size - 1)
	{
		j = 0;
		while (j < size - i - 1)
		{
			if (tab[j] > tab[j + 1])
			{
				tmp = tab[j];
				tab[j] = tab[j + 1];
				tab[j + 1] = tmp;
			}
			j++;
		}
		i++;
	}
}

/*
#include <stdio.h>

void	print_array(int *tab, unsigned int size)
{
	unsigned int	i = 0;
	while (i < size)
	{
		printf("%d ", tab[i]);
		i++;
	}
	printf("\n");
}

int	main(void)
{
	int	arr1[] = {3, 1, 4, 2};
	int	arr2[] = {5};
	int	arr3[] = {2, 2, 1, 1, 3, 3};
	int	arr4[] = {-1, -5, 0, 3, -2};

	printf("Before: ");
	print_array(arr1, 4);
	sort_int_tab(arr1, 4);
	printf("After: ");
	print_array(arr1, 4);

	printf("\nBefore: ");
	print_array(arr2, 1);
	sort_int_tab(arr2, 1);
	printf("After: ");
	print_array(arr2, 1);

	printf("\nBefore: ");
	print_array(arr3, 6);
	sort_int_tab(arr3, 6);
	printf("After: ");
	print_array(arr3, 6);

	printf("\nBefore: ");
	print_array(arr4, 5);
	sort_int_tab(arr4, 5);
	printf("After: ");
	print_array(arr4, 5);

	return (0);
}
*/