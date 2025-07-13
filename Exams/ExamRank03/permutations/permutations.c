/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   permutations.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erazumov <erazumov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/13 14:54:34 by erazumov          #+#    #+#             */
/*   Updated: 2025/07/13 15:23:51 by erazumov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

int	ft_strlen(char *str)
{
	int	len;

	len = 0;
	while (str[len] != '\0')
		len++;
	return (len);
}

void	ft_swap(char *a, char *b)
{
	char	tmp;

	tmp = *a;
	*a = *b;
	*b = tmp;
}

void	sort_str(char *str)
{
	int	i;
	int	j;
	int	len;

	len = ft_strlen(str);
	i = 0;
	while (i < len - 1)
	{
		j = 0;
		while (j < len - i - 1)
		{
			if (str[j] > str[j + 1])
				ft_swap(&str[j], &str[j + 1]);
			j++;
		}
		i++;
	}
}

void	find_permutations(char *orig_str, char *curr_perm, int *used,
	int k, int len)
{
	int	i;

	// Cas de base : la permutation a atteint la bonne longueur
	if (k == len)
	{
		puts(curr_perm);
		return ;
	}
	// On parcourt toutes les lettres de la chaîne originale
	i = 0;
	while (i < len)
	{
		// Si la lettre n'a pas encore été utilisée pour CETTE permutation...
		if (used[i] == 0)
		{
			// On l'ajoute à la position k de notre permutation en cours
			curr_perm[k] = orig_str[i];
			used[i] = 1; // Utilisée
			// Trouve la lettre suivante (à la position k+1)
			find_permutations(orig_str, curr_perm, used, k + 1, len);
			/* "Retour sur trace" : une fois que l'appel ci-dessus est
				terminé, on libère la lettre pour qu'elle puisse être
				utilisée dans d'autres permutations. */
			used[i] = 0;
		}
		i++;
	}
}

int	main(int ac, char **av)
{
	char	*input_str;
	char	*curr_perm;
	int		*used;
	int		len;

	if (ac != 2)
		return (1);

	input_str = av[1];
	len = ft_strlen(input_str);

	// Trier la chaîne d'entrée
	sort_str(input_str);

	// Allouer la mémoire
	curr_perm = malloc(sizeof(char) * (len + 1));
	used = calloc(len, sizeof(int)); // calloc met tout à 0
	if (!curr_perm || !used)
		return (1); // Erreur d'allocation
	curr_perm[len] = '\0'; // Toujours terminer la chaîne !

	// Lancer la recherche de permutations
	find_permutations(input_str, curr_perm, used, 0, len);

	// Libérer la mémoire
	free(curr_perm);
	free(used);

	return (0);
}
