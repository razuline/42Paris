/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rip.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erazumov <erazumov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/13 16:30:32 by erazumov          #+#    #+#             */
/*   Updated: 2025/07/15 16:02:11 by erazumov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rip.h"

// Fonction utilitaire pour calculer la longueur de la chaîne
int	ft_strlen(char *str)
{
	int	len;

	len = 0;
	while (str[len])
		len++;
	return (len);
}

/**
 * @brief Fonction récursive qui génère et affiche toutes les solutions valides.
 * @param str La chaîne de caractères (modifiée sur place).
 * @param index La position actuelle dans la chaîne.
 * @param left_rem Le nombre de '(' qu'il reste à retirer.
 * @param right_rem Le nombre de ')' qu'il reste à retirer.
 * @param balance Le bilan actuel des parenthèses (doit toujours être >= 0).
 */
void	generate(char *str, int idx, int left_rem, int right_rem, int balance)
{
	char	curr_ch;

	// Cas de base : on est à la fin de la chaîne
	if (str[idx] == '\0')
	{
		// Si on a retiré le bon nombre de parenthèses ET
		// que la chaîne est équilibrée
		if (left_rem == 0 && right_rem == 0 && balance == 0)
			puts(str); // On affiche la solution
		return ;
	}
	curr_ch = str[idx];
	// Si le caractère est '(': on explore deux possibilités
	if (curr_ch == '(')
	{
		// 1. On le RETIRE (s'il nous en reste à retirer)
		if (left_rem > 0)
		{
			str[idx] = ' '; // On le remplace par un espace
			generate(str, idx + 1, left_rem - 1, right_rem, balance + 1);
			str[idx] = '('; // BACKTRACK: on le remet en place pour
							// les autres explorations
		}
		// 2. On le GARDE
		generate(str, idx + 1, left_rem, right_rem, balance + 1);
	}
	// Si le caractère est ')': on explore deux possibilités
	else if (curr_ch == ')')
	{
		// 1. On le RETIRE (s'il nous en reste à retirer)
		if (right_rem > 0)
		{
			str[idx] = ' '; // On le remplace par un espace
			generate(str, idx + 1, left_rem, right_rem - 1, balance);
			str[idx] = ')'; // BACKTRACK: on le remet en place
		}
		// 2. On le GARDE (seulement si la chaîne reste valide)
		if (balance > 0)
			generate(str, idx + 1, left_rem, right_rem, balance);
	}
}

int	main(int ac, char **av)
{
	char	*input;
	int		i;
	int		left_to_remove;
	int		right_to_remove;

	if (ac != 2)
	{
		write(1, "\n", 1);
		return (0);
	}
	input = av[1];
	left_to_remove = 0;
	right_to_remove = 0;
	// --- Étape 1 : Compter les parenthèses à retirer ---
	i = 0;
	while (input[i])
	{
		if (input[i] == '(')
			left_to_remove++;
		else if (input[i] == ')')
		{
			if (left_to_remove > 0)
				left_to_remove--; // Cette ')' ferme une '('
			else
				right_to_remove++; // Cette ')' est en trop
		}
		i++;
	}
	// --- Étape 2 : Lancer la génération des solutions ---
	generate(input, 0, left_to_remove, right_to_remove, 0);
	return (0);
}
