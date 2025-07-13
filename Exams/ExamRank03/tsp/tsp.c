/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tsp.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erazumov <erazumov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/13 16:29:29 by erazumov          #+#    #+#             */
/*   Updated: 2025/07/13 16:40:02 by erazumov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <stdbool.h>
#include <sys/types.h>

float	distance(float a[2], float b[2])
{
	return sqrtf((b[0] - a[0]) * (b[0] - a[0]) + (b[1] - a[1]) * (b[1] - a[1]));
}

float tsp(float (*array)[2], ssize_t size)
{
	if (size <= 1)
	{
		return 0.0;
	}

	// --- Étape 1: Pré-calculer la matrice des distances ---
	float distances[size][size];
	for (ssize_t i = 0; i < size; i++) {
		for (ssize_t j = 0; j < size; j++) {
			distances[i][j] = distance(array[i], array[j]);
		}
	}

	// --- Étape 2: Préparer les variables pour la récursion ---
	float min_length = INFINITY; // Commence avec une longueur "infinie"
	int path[size];              // Pour stocker le chemin actuel
	bool visited[size];          // Pour marquer les villes visitées
	
	// Initialiser le tableau visited à false
	for (ssize_t i = 0; i < size; i++) {
		visited[i] = false;
	}

	// --- Étape 3: Lancer la récursion ---
	// On fixe le point de départ à la ville 0 pour optimiser
	path[0] = 0;
	visited[0] = true;

	// On commence à chercher le chemin à partir de la 2ème ville (profondeur 1)
	solve_recursive(size, distances, path, visited, 1, &min_length);

	return (min_length);
}