/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erazumov <erazumov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 12:42:37 by erazumov          #+#    #+#             */
/*   Updated: 2025/07/23 12:42:46 by erazumov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h> // Pour le vrai scanf de comparaison

// Déclarez votre fonction pour que le main la connaisse
int	ft_scanf(const char *format, ...);

int	main(void)
{
	int		d;
	char	c;
	char	s[100];
	int		ret;

	// --- Test 1: Lire un entier ---
	printf("Entrez un nombre : ");
	ret = ft_scanf("%d", &d);
	printf("ft_scanf a retourné %d. Nombre lu : %d\n", ret, d);

	// --- Test 2: Lire un mot ---
	printf("\nEntrez un mot : ");
	ret = ft_scanf("%s", s);
	printf("ft_scanf a retourné %d. Mot lu : %s\n", ret, s);

	// --- Test 3: Lire un caractère ---
	printf("\nEntrez un caractère : ");
	ret = ft_scanf("%c", &c);
	printf("ft_scanf a retourné %d. Caractère lu : %c\n", ret, c);

	// --- Test 4: Format complexe ---
	printf("\nEntrez 'age: <nombre>' : ");
	ret = ft_scanf("age: %d", &d);
	printf("ft_scanf a retourné %d. Age lu : %d\n", ret, d);
	
	return (0);
}
