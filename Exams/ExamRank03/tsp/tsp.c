/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tsp.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erazumov <erazumov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/13 16:29:29 by erazumov          #+#    #+#             */
/*   Updated: 2025/07/19 13:44:32 by erazumov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <stdbool.h>
#include <float.h>
#include <sys/types.h>

// compute the distance between two points
float    distance(float a[2], float b[2])
{
	return (sqrtf((b[0] - a[0]) * (b[0] - a[0]) + (b[1] - a[1]) * (b[1] - a[1])));
}
// Mon code
static void	solve_tsp_recursive(ssize_t size, float distances[size][size],
	int *path, bool *visited, int depth, float *min_length)
{
	// Cas de base : un chemin complet a été formé
	if (depth == size)
	{
		float current_length = 0;
		int i = 0;

		// Calcule la longueur du chemin
		while (i < size - 1)
		{
			current_length += distances[path[i]][path[i + 1]];
			i++;
		}
		// Ajoute la distance pour retourner au point de départ
		current_length += distances[path[size - 1]][path[0]];

		// Met à jour la distance minimale si ce chemin est plus court
		if (current_length < *min_length)
			*min_length = current_length;
		return;
	}

	// Étape récursive : essaie chaque ville non visitée comme prochaine étape
	int i = 0;
	while (i < size)
	{
		if (!visited[i])
		{
			path[depth] = i;
			visited[i] = true;
			solve_tsp_recursive(size, distances, path, visited, depth + 1, min_length);
			visited[i] = false; // Backtrack
		}
		i++;
	}
}

// Fonction principale à insérer dans votre fichier
float	tsp(float (*cities)[2], ssize_t size)
{
	if (size <= 1)
		return (0.0);

	// 1. Pré-calcul de la matrice des distances
	float	distances[size][size];
	for (ssize_t i = 0; i < size; i++)
		for (ssize_t j = 0; j < size; j++)
			distances[i][j] = distance(cities[i], cities[j]);

	// 2. Initialisation pour la récursion
	float	min_length = INFINITY;
	int		path[size];
	bool	visited[size];
	for (ssize_t i = 0; i < size; i++)
		visited[i] = false;

	// 3. On fixe la ville 0 comme point de départ
	path[0] = 0;
	visited[0] = true;

	// 4. Lancement de la recherche récursive pour le reste du chemin
	solve_tsp_recursive(size, distances, path, visited, 1, &min_length);
	
	return (min_length);
}
// Fin
ssize_t    file_size(FILE *file)
{
	char    *buffer = NULL;
	size_t    n = 0;
	ssize_t ret;

	errno = 0;

	for (ret = 0; getline(&buffer, &n, file) != -1; ret++);

	free(buffer);
	if (errno || fseek(file, 0, SEEK_SET))
		return -1;
	return ret;
}

int        retrieve_file(float (*array)[2], FILE *file)
{
	int tmp;
	for (size_t i = 0; (tmp = fscanf(file, "%f, %f\n", array[i] + 0, array[i] + 1)) != EOF; i++)
		if (tmp != 2)
		{
			errno = EINVAL;
			return -1;
		}
	if (ferror(file))
		return -1;
	return 0;
}

int        main(int ac, char **av)
{
	char *filename = "stdin";
	FILE *file = stdin;
	if (ac > 1)
	{
		filename = av[1];
		file = fopen(filename, "r");
	}

	if (!file)
	{
		fprintf(stderr, "Error opening %s: %m\n", filename);
		return 1;
	}

	ssize_t size = file_size(file);
	if (size == -1)
	{
		fprintf(stderr, "Error reading %s: %m\n", filename);
		fclose(file);
		return 1;
	}

	float (*array)[2] = calloc(size, sizeof (float [2]));
	if (!array)
	{
		fprintf(stderr, "Error: %m\n");
		fclose(file);
		return 1;
	}

	if (retrieve_file(array, file) == -1)
	{
		fprintf(stderr, "Error reading %s: %m\n", av[1]);
		fclose(file);
		free(array);
		return 1;
	}
	if (ac > 1)
		fclose(file);

	printf("%.2f\n", tsp(array, size));
	free(array);
	return (0);
}
